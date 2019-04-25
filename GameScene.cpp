#include "GameScene.h"
#include "MenuScene.h"
#include "HighscoreScene.h"
#include <iostream>


GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	input = InputUtils::InputManager::Instance();
	SDL_Renderer* renderer = game.getRenderer();

	//Load the sound effects
	cPaddle = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (1).wav");
	cBrick = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (2).wav");
	cBottom = Mix_LoadWAV(".\\sounds\\doh.wav");
	cSides = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (3).wav");
	cNextRound = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (9).wav");
	cGameOver = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (11).wav");

	//Game objects
	paddle = new Paddle(renderer);
	ball = new Ball(renderer);
	level = new Level(renderer);
	highscore = new Highscores();

	//set paddle height to correct height
	paddle->y = level->height - paddle->height;

	//Create start level
	level->NextLevel(CurrentLevel);


}
GameScene::~GameScene()
{
	delete paddle;
	delete ball;
	delete level;
	delete highscore;
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

	UpdatePaddlePosition();
	UpdateBallCheckReleased();

	//Collision detection
	UpdatePaddleCollisionDetection();
	UpdateLevelCollisionDetectionMove();
	UpdateMapCollisionDetection();
}
void GameScene::ResetBall() {
	//Remove 1 life
	Life--;
	ball->released = false;
	update_stats_lives();
	ball->set_direction(EASY_BALL_SPEED, 100);
}
void GameScene::LevelUp() {
	int brick_count = GetBrickNum();
	std::cout << "Bricks left:" << brick_count << std::endl;
	if (brick_count== 0) {
		highscore->readFile();
		highscore->writeFile(Score);
		// Rest the ball to paddle with next level
		ball->released = false;
		ball->set_direction(EASY_BALL_SPEED, 100);
		level->NextLevel(CurrentLevel);
		if (CurrentLevel == 3) {
			CurrentLevel = 0; // reset level to loop
			Difficulty++; // increase Difficulty after next loop
			ball->ball_difficulty = 1 + (Difficulty / 4);
		}
		CurrentLevel++;
		level->NextLevel(CurrentLevel);
		Mix_PlayChannel(-1, cNextRound, 0);
		
		update_stats_level();
	}
}
void GameScene::UpdateLevelCollisionDetectionMove() {
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];

			// Check if brick is present
			if (brick.state) {
				// Brick x and y coordinates
				float brickx = level->brickoffsetx + level->x + i * LEVEL_BRWIDTH;
				float bricky = level->brickoffsety + level->y + j * LEVEL_BRHEIGHT;

				// Center of the ball x and y coordinates
				float ballcenterx = ball->x + 0.5f*ball->width;
				float ballcentery = ball->y + 0.5f*ball->height;

				// Center of the brick x and y coordinates
				float brickcenterx = brickx + 0.5f*LEVEL_BRWIDTH;
				float brickcentery = bricky + 0.5f*LEVEL_BRHEIGHT;

				if (ball->x <= brickx + LEVEL_BRWIDTH && ball->x + ball->width >= brickx && ball->y <= bricky + LEVEL_BRHEIGHT && ball->y + ball->height >= bricky) {
					// Collision detected, remove the brick
					Mix_PlayChannel(-1, cBrick, 0);
					if (brick.hp == 0) {
						level->bricks[i][j].state = false;
					}
					else {
						level->bricks[i][j].hp -= 1;
						/*if (brick.type == 0) {
							level->bricks[i][j].type = 2;
						}*/
					}

					if (brick.hp >= 0) {
						Score++;
						update_stats_score();
					}

					// Calculate ysize
					float ymin = 0;
					if (bricky > ball->y) {
						ymin = bricky;
					}
					else {
						ymin = ball->y;
					}

					float ymax = 0;
					if (bricky + LEVEL_BRHEIGHT < ball->y + ball->height) {
						ymax = bricky + LEVEL_BRHEIGHT;
					}
					else {
						ymax = ball->y + ball->height;
					}

					float ysize = ymax - ymin;

					// Calculate xsize
					float xmin = 0;
					if (brickx > ball->x) {
						xmin = brickx;
					}
					else {
						xmin = ball->x;
					}

					float xmax = 0;
					if (brickx + LEVEL_BRWIDTH < ball->x + ball->width) {
						xmax = brickx + LEVEL_BRWIDTH;
					}
					else {
						xmax = ball->x + ball->width;
					}

					float xsize = xmax - xmin;

					// The origin is at the top-left corner of the screen!
					// Set collision response
					if (xsize > ysize) {
						if (ballcentery > brickcentery) {
							// Bottom
							ball->y += ysize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::bottom);
							std::cout << "Brick hit bottom" << std::endl;
						}
						else {
							// Top
							ball->y -= ysize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::top);
							std::cout << "Brick hit top" << std::endl;
						}
					}
					else {
						if (ballcenterx < brickcenterx) {
							// Left
							ball->x -= xsize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::left);
							std::cout << "Brick hit left" << std::endl;
						}
						else {
							// Right
							ball->x += xsize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::right);
							std::cout << "Brick hit right" << std::endl;
						}
					}

					return;
				}
			}
		}
	}
}
void GameScene::brick_hit(brick_hit_face face) {
	// dirindex 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->m_dirX > 0) {
		// Ball is moving in the positive x direction
		if (ball->m_dirY > 0) {
			// Ball is moving in the positive y direction
			// +1 +1
			if (face == brick_hit_face::left || face == brick_hit_face::right) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->m_dirY < 0) {
			// Ball is moving in the negative y direction
			// +1 -1
			if (face == brick_hit_face::left || face == brick_hit_face::right) {
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
			//
			if (face == brick_hit_face::left || face == brick_hit_face::right) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->m_dirY < 0) {
			// Ball is moving in the negative y direction
			// -1 -1
			if (face == brick_hit_face::left || face == brick_hit_face::right) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	ball->set_direction(muly*ball->m_dirY, mulx*ball->m_dirX);
	LevelUp();
}

// Contains gameover logic when ball hits bottom
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
			// TODO
			// quit to highscore()
			// Update Score()
			// Temp solutions, quit to menu, did not work

			mGame.enterScene(std::make_shared<HighscoreScene>(mGame));
			return;

			
		}
		else{
			Mix_PlayChannel(-1, cBottom, 0);
		}

	}

	// Left and right collisions
	if (ball->x <= level->x + level->brickoffsetx) {
		// Left
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x + level->brickoffsetx;
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
		ball->set_direction(EASY_BALL_SPEED,EASY_BALL_SPEED * GetReflection(ballcenterx - paddle->x));
		Mix_PlayChannel(-1, cPaddle, 0);
	}
}
void GameScene::UpdatePaddlePosition() {
	static int oldx;
	if (oldx != input->getX()) {
		paddle->x = input->getX() - paddle->width / 2.0f;
		oldx = input->getX();
	}
	if (move_left) {
		paddle->x -= 0.5;
	}
	if (move_right) {
		paddle->x+=0.5;
	}

	if (paddle->x < level->brickoffsetx) { paddle->x = level->brickoffsetx; }
	if (paddle->x > (level->width - paddle->width + level->brickoffsetx)) {
		paddle->x = (level->width - paddle->width + level->brickoffsetx);
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
int GameScene::GetBrickNum() {
	int bricknum = 0;
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];
			if (brick.state && brick.hp >= 0) { // Does not count industribable bricks
				bricknum++;
			}
		}
	}
	return bricknum;
}
//Create/draw/update status

void GameScene::update_stats_lives() {
	if (mLivesText) SDL_DestroyTexture(mLivesText);

	TTF_Font* font = mGame.getFont();
	SDL_Renderer* renderer = mGame.getRenderer();

	auto sLivesText = "Lives: " + std::to_string(Life);
	mLivesText = TextureManager::create_text(sLivesText, renderer, font);
	SDL_QueryTexture(mLivesText, nullptr, nullptr, &mLivesTextPosition.w, &mLivesTextPosition.h);
	mLivesTextPosition.y = stats_height_margin * 4;
	mLivesTextPosition.x = level->width + stats_left_margin;
}
void GameScene::update_stats_score() {

	if (mScoreText) SDL_DestroyTexture(mScoreText);

	TTF_Font* font = mGame.getFont();
	SDL_Renderer* renderer = mGame.getRenderer();

	auto sScoreText = "Score: " + std::to_string(Score);
	mScoreText = TextureManager::create_text(sScoreText, renderer, font);
	SDL_QueryTexture(mScoreText, nullptr, nullptr, &mScoreTextPosition.w, &mScoreTextPosition.h);
	mScoreTextPosition.y = stats_height_margin * 5;
	mScoreTextPosition.x = level->width + stats_left_margin;
}
void GameScene::update_stats_difficulty() {

	if (mDifficultyText) SDL_DestroyTexture(mDifficultyText);

	TTF_Font* font = mGame.getFont();
	SDL_Renderer* renderer = mGame.getRenderer();

	auto sDifficultyText = "Difficulty: " + std::to_string(Difficulty);
	mDifficultyText = TextureManager::create_text(sDifficultyText, renderer, font);
	SDL_QueryTexture(mDifficultyText, nullptr, nullptr, &mDifficultyTextPosition.w, &mDifficultyTextPosition.h);
	mDifficultyTextPosition.y = stats_height_margin * 6;
	mDifficultyTextPosition.x = level->width + stats_left_margin;

}
void GameScene::update_stats_level() {

	if (mLevelText) SDL_DestroyTexture(mLevelText);

	TTF_Font* font = mGame.getFont();
	SDL_Renderer* renderer = mGame.getRenderer();

	auto sLevelText = "Level: " + std::to_string(CurrentLevel);
	mLevelText = TextureManager::create_text(sLevelText, renderer, font);
	SDL_QueryTexture(mLevelText, nullptr, nullptr, &mLevelTextPosition.w, &mLevelTextPosition.h);
	mLevelTextPosition.y = stats_height_margin * 7;
	mLevelTextPosition.x = level->width + stats_left_margin;

}
void GameScene::update_logo() {

	if (mLogo) SDL_DestroyTexture(mLogo);

	SDL_Renderer* renderer = mGame.getRenderer();

	mLogo = mLogo = TextureManager::load_texture(".\\textures\\logo.png", renderer);
	mLogoPosition.h = 100;
	mLogoPosition.w = 200;
	mLogoPosition.x = level->width + stats_left_margin;
	mLogoPosition.y = 30;
}

//Events
void GameScene::enter()
{
	update_stats_difficulty();
	update_stats_level();
	update_stats_lives();
	update_stats_score();
	update_logo();
}
void GameScene::exit()
{

}
void GameScene::keyUp(SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym) {
	case SDLK_LEFT:
		move_left = false;
		break;
	case SDLK_RIGHT:
		move_right = false;
		break;
	}
}
void GameScene::keyDown(SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym) {
	case SDLK_ESCAPE:
		mGame.enterScene(std::make_shared<MenuScene>(mGame));
		break;
	case SDLK_LEFT: 
		move_left = true;
		break;
	case SDLK_RIGHT:
		move_right = true;
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
