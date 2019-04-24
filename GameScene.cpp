#include "GameScene.h"
#include <iostream>

GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	SDL_Renderer *renderer = game.getRenderer();
	paddle = new Paddle(renderer);
	ball = new Ball(".\\textures\\blueBox.png",renderer);
	level = new Level(renderer);

	//Create start level
	/*TODO*/// Need to create logic for game end... if bricks[][] == empty -> level->CreateRound2();
	level->CreateRound1();
}

void GameScene::NewGame() {
	level->CreateRound1();
	ResetPlayer();
}

GameScene::~GameScene()
{
	std::cout << "GameScene destroyed";
	
}

void GameScene::update(unsigned int dt)
{
	paddle->update(dt);
	ball->update(dt);
	level->update(dt);
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
}
