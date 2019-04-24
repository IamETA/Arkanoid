#include "GameScene.h"
#include "MenuScene.h"
#include <iostream>

GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	input = InputUtils::InputManager::Instance();
	SDL_Renderer *renderer = game.getRenderer();

	paddle = new Paddle(renderer);
	ball = new Ball(".\\textures\\blueBox.png", renderer);
	level = new Level(renderer);

	paddle->y = level->height - paddle->height;

	//paddle = new Paddle(renderer);
	//ball = new Ball(".\\textures\\blueBox.png",renderer);
	//level = new Level(renderer);

	//Create start level
	/*TODO*/// Need to create logic for game end... if bricks[][] == empty -> level->CreateRound2();
	level->CreateRound1();
}

GameScene::~GameScene()
{
	std::cout << "GameScene destroyed";
	
}

void GameScene::update(float delta)
{
	paddle->update(delta);
	ball->update(delta);
	level->update(delta);

	UpdatePaddlePosition();
	UpdateBallCheckReleased();
	UpdateMapCollisionDetection();
}
void GameScene::ResetBall() {
	//Remove 1 life
	ball->released = false;
	ball->set_direction(1, 1);
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
		ball->set_direction(GetReflection(ballcenterx - paddle->x), -1);
		//ball->SetDirection(0, -1);
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
