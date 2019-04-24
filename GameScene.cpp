#include "GameScene.h"
#include "MenuScene.h"
#include <iostream>

GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	input = InputUtils::InputManager::Instance();
	SDL_Renderer *renderer = game.getRenderer();

	//Game objects
	paddle = new Paddle(renderer);
	ball = new Ball(renderer);
	level = new Level(renderer);


	paddle->y = level->height - paddle->height;


	//Create start level
	/*TODO*/// Need to create logic for game end... if bricks[][] == empty -> level->CreateRound2();
	level->CreateRound1();
}

GameScene::~GameScene()
{
	delete paddle;
	delete ball;
	delete level;
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
	UpdateMapCollisionDetection();
	UpdatePaddleCollisionDetection();
	UpdateLevelCollisionDetection();
}
void GameScene::ResetBall() {
	//Remove 1 life
	ball->released = false;
	ball->set_direction(1, 1);
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
	}
	else if (ball->y + ball->height > level->y + level->height) {
		// Bottom

		// Ball lost
		ResetBall();
	}

	// Left and right collisions
	if (ball->x <= level->x) {
		// Left
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x;
		ball->m_dirX *= -1;
	}
	else if (ball->x + ball->width >= level->x + level->width) {
		// Right
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x + level->width - ball->width;
		ball->m_dirX *= -1;
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
