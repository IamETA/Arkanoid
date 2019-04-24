#include "GameScene.h"

GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene...";

	SDL_Renderer *renderer = game.getRenderer();
	paddle = new Paddle(renderer);
	ball = new Ball(".\\textures\\blueBox.png",renderer);
	level = new Level(renderer);
	//Create start level
	level->CreateRound1();
}

GameScene::~GameScene()
{
	delete paddle;
	delete ball;
	delete level;
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
