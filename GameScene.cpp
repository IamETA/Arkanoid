#include "GameScene.h"
#include "MenuScene.h"
#include <iostream>

GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	input = InputUtils::InputManager::Instance();
	SDL_Renderer* renderer = game.getRenderer();

	/* Sounds
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	} */

	//Load the sound effects
	cPaddle = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (1).wav");
	cBrick = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (2).wav");
	cBottom = Mix_LoadWAV(".\\sounds\\doh.wav");
	cSides = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (3).wav");
	cNextRound = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (9).wav");
	cGameOver = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (10).wav");

	//If there was a problem loading the sound effects
	/*
	if ((cPaddle == NULL) || (cBrick == NULL) || (cBottom == NULL) || (cSides == NULL) || (cNextRound == NULL) || (cGameOver == NULL))
	{
		return false;
	} */

	//Game objects
	paddle = new Paddle(renderer);
	ball = new Ball(renderer);
	level = new Level(renderer);

	//set paddle height to correct height
	paddle->y = level->height - paddle->height;



	//Create start level
	/*TODO*/// Need to create logic for game end... if bricks[][] == empty -> level->CreateRound2();
	level->CreateRound1();
}
void GameScene::UpdateStats() {
	const int margin{ 60 };
	const int hmargin{ 60 };
	if (mLivesText) SDL_DestroyTexture(mLivesText);
	if (mScoreText) SDL_DestroyTexture(mScoreText);
	if (mDifficultyText) SDL_DestroyTexture(mDifficultyText);
	if (mLevelText) SDL_DestroyTexture(mLevelText);
	if (mLogo) SDL_DestroyTexture(mLogo);


	TTF_Font* font = mGame.getFont();
	SDL_Renderer* renderer = mGame.getRenderer();

	auto sLivesText = "Lives: " + std::to_string(Life);
	mLivesText = TextureManager::create_text(sLivesText, renderer, font);
	SDL_QueryTexture(mLivesText, nullptr, nullptr, &mLivesTextPosition.w, &mLivesTextPosition.h);
	mLivesTextPosition.y = hmargin * 4;
	mLivesTextPosition.x = level->width + margin;
	

	auto sScoreText = "Score: " + std::to_string(Score);
	mScoreText = TextureManager::create_text(sScoreText, renderer, font);
	SDL_QueryTexture(mScoreText, nullptr, nullptr, &mScoreTextPosition.w, &mScoreTextPosition.h);
	mScoreTextPosition.y = hmargin * 5;
	mScoreTextPosition.x = level->width + margin;

	auto sDifficultyText = "Difficulty: " + std::to_string(Difficulty);
	mDifficultyText = TextureManager::create_text(sDifficultyText, renderer, font);
	SDL_QueryTexture(mDifficultyText, nullptr, nullptr, &mDifficultyTextPosition.w, &mDifficultyTextPosition.h);
	mDifficultyTextPosition.y = hmargin * 6;
	mDifficultyTextPosition.x = level->width + margin;

	auto sLevelText = "Level: " + std::to_string(CurrentLevel);
	mLevelText = TextureManager::create_text(sLevelText, renderer, font);
	SDL_QueryTexture(mLevelText, nullptr, nullptr, &mLevelTextPosition.w, &mLevelTextPosition.h);
	mLevelTextPosition.y = hmargin * 7;
	mLevelTextPosition.x = level->width + margin;

	mLogo  = mLogo = TextureManager::load_texture(".\\textures\\logo.png", renderer);
	mLogoPosition.h = 100; 
	mLogoPosition.w = 200;
	mLogoPosition.x = level->width + margin;
	mLogoPosition.y = 30;
}
GameScene::~GameScene()
{
	delete paddle;
	delete ball;
	delete level;
	//Free the sound effects
	Mix_FreeChunk(cBrick);
	Mix_FreeChunk(cBottom);
	Mix_FreeChunk(cPaddle);
	Mix_FreeChunk(cNextRound);
	Mix_FreeChunk(cSides);
	Mix_FreeChunk(cGameOver);

	std::cout << "GameScene destroyed";
	
}

void GameScene::update(float delta)
{
	paddle->update(delta);
	ball->update(delta);
	level->update(delta);

	UpdateStats();
	UpdatePaddlePosition();
	UpdateBallCheckReleased();
	NewRound();

	//Collision detection
	UpdateMapCollisionDetection();
	UpdatePaddleCollisionDetection();
	UpdateLevelCollisionDetection();
}
void GameScene::ResetBall() {
	//Remove 1 life
	Life--;
	ball->released = false;
	ball->set_direction(1, 1);
}

void GameScene::NewRound() {
	/*if (GetBrickCount() == 0) {
		round++; //Next round in game.
		NewGame();
		level->CreateRound1();
	}
	level->CreateLevel(round);
	ResetPlayer();
	round++; //Next round in game.*/
}

void GameScene::UpdateLevelCollisionDetection() {
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];

			// Check if brick is present
			if (brick.state) {
				// Brick x and y coordinates
				float brickx = level->brickoffsetx + level->x + i * LEVEL_BRWIDTH;
				float bricky = level->brickoffsety + level->y + j * LEVEL_BRHEIGHT;

				// Check ball-brick collision
				// Determine the collision using the half-widths of the rectangles
				float w = 0.5f * (ball->width + LEVEL_BRWIDTH);
				float h = 0.5f * (ball->height + LEVEL_BRHEIGHT);
				float dx = (ball->x + 0.5f*ball->width) - (brickx + 0.5f*LEVEL_BRWIDTH);
				float dy = (ball->y + 0.5f*ball->height) - (bricky + 0.5f*LEVEL_BRHEIGHT);

				if (fabs(dx) <= w && fabs(dy) <= h) {
					// Collision detected
					Mix_PlayChannel(-1, cBrick, 0);
					if (brick.hp == 0) {
						level->bricks[i][j].state = false;
					}
					else {
						level->bricks[i][j].hp -= 1;
						if (brick.type == 0) {
							level->bricks[i][j].type = 2; // Green Brick
						}
					}

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx) {
						if (wy > -hx) {
							// Bottom (y is flipped)
							BallBrickResponse(3);
						}
						else {
							// Left
							BallBrickResponse(0);
						}
					}
					else {
						if (wy > -hx) {
							// Right
							BallBrickResponse(2);
						}
						else {
							// Top (y is flipped)
							BallBrickResponse(1);
						}
					}
					return;
				}
			}
		}
	}
}

void GameScene::BallBrickResponse(int dirindex) {
	// dirindex 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->m_dirX > 0) {
		// Ball is moving in the positive x direction
		if (ball->m_dirY > 0) {
			// Ball is moving in the positive y direction
			// +1 +1
			if (dirindex == 0 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->m_dirY < 0) {
			// Ball is moving in the negative y direction
			// +1 -1
			if (dirindex == 0 || dirindex == 1) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}
	else if (ball->m_dirX < 0) {
		// Ball is moving in the negative x direction
		if (ball->m_dirY > 0) {
			// Ball is moving in the positive y direction
			// -1 +1
			if (dirindex == 2 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->m_dirY < 0) {
			// Ball is moving in the negative y direction
			// -1 -1
			if (dirindex == 1 || dirindex == 2) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	ball->set_direction(mulx*ball->m_dirX, muly*ball->m_dirY);
}
void GameScene::UpdateMapCollisionDetection() {
	// Top and bottom collisions
	if (ball->y < level->y) {
		// Top
		// Keep the ball within the level and reflect the y-direction
		ball->y = level->y;
		ball->m_dirY *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
	else if (ball->y + ball->height > level->y + level->height) {
		// Bottom

		// Ball lost
		ResetBall();
		if (Life == 0) {
			Mix_PlayChannel(-1, cGameOver, 0);
			// quit to highscore()
			// Update Score()
		}
		else{
			Mix_PlayChannel(-1, cBottom, 0);
		}

	}

	// Left and right collisions
	if (ball->x <= level->x) {
		// Left
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x;
		ball->m_dirX *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
	else if (ball->x + ball->width >= level->x + level->width) {
		// Right
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x + level->width - ball->width;
		ball->m_dirX *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
}

float GameScene::GetReflection(float hitx) {
	// Make sure the hitx variable is within the width of the player
	if (hitx < 0) {
		hitx = 0;
	}
	else if (hitx > paddle->width) {
		hitx = paddle->width;
	}

	// Everything to the left of the center of the paddle is reflected to the left
	// while everything right of the center is reflected to the right
	hitx -= paddle->width / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitx / (paddle->width / 2.0f));
}

void GameScene::UpdatePaddleCollisionDetection() {
	// Get the center x-coordinate of the ball
	float ballcenterx = ball->x + ball->width / 2.0f;

	// Check player collision
	if (ball->collision_with(paddle)) {
		ball->y = paddle->y - ball->height;
		ball->set_direction(1,GetReflection(ballcenterx - paddle->x));
		Mix_PlayChannel(-1, cPaddle, 0);
	}
}

void GameScene::UpdatePaddlePosition() {
	paddle->x = input->getX() - paddle->width / 2.0f;
	if (paddle->x < 0) { paddle->x = 0; }
	if (paddle->x > (level->width - paddle->width)) {
		paddle->x = (level->width - paddle->width);
	}
}

void GameScene::UpdateBallCheckReleased() {
	if (!ball->released) {
		ball->x = paddle->x + paddle->width / 2 - ball->width / 2;
		ball->y = paddle->y - ball->height;
	}
}

void GameScene::render()
{
	paddle->render();
	ball->render();
	level->render();


	//render stats
	SDL_Renderer* renderer = mGame.getRenderer();
	SDL_RenderCopy(renderer, mLivesText, nullptr, &mLivesTextPosition);
	SDL_RenderCopy(renderer, mScoreText, nullptr, &mScoreTextPosition);
	SDL_RenderCopy(renderer, mDifficultyText, nullptr, &mDifficultyTextPosition);
	SDL_RenderCopy(renderer, mLevelText, nullptr, &mLevelTextPosition);
	SDL_RenderCopy(renderer, mLogo, nullptr, &mLogoPosition);
	//SDL_RenderCopy(renderer, mLogo, nullptr, &mLivesTextPosition);
}

int GameScene::GetBrickCount() {
	int brickcount = 0;
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];
			if (brick.state) {
				brickcount++;
			}
		}
	}
	return brickcount;
}

void GameScene::enter()
{
}


void GameScene::exit()
{
}

void GameScene::keyUp(SDL_KeyboardEvent & event)
{

}

void GameScene::keyDown(SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym) {
	case SDLK_ESCAPE:
		mGame.enterScene(std::make_shared<MenuScene>(mGame));
		break;
	}

}

void GameScene::mouseDown(SDL_KeyboardEvent & event)
{
	/*
	switch (event.keysym.sym) {
	case SDLK_|:
		mGame.enterScene(std::make_shared<MenuScene>(mGame));
		break;
	}*/
	ball->released = true;

}
