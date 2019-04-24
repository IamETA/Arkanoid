#include "GameScene.h"
#include <iostream>

GameScene::GameScene(Game& game) : Scene(game)
{
	SDL_Renderer *renderer = game.getRenderer();

	paddle = std::make_unique<Paddle>(renderer);
	ball = std::make_unique<Ball>(".\\textures\\blueBox.png", renderer);
	level = std::make_unique<Level>(renderer);


	//Create start level
	/*TODO*/// Need to create logic for game end... if bricks[][] == empty -> level->CreateRound2();
	level->CreateRound1();
}

GameScene::~GameScene()
{
	std::cout << "GameScene destroyed";
	
}

void GameScene::update(float dt)
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
