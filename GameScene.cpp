#include "GameScene.h"


using namespace Game;

GameScene::GameScene(Game& game) : Scene(game)
{
	SDL_Renderer renderer* = game->getRenderer();
	paddle = new Paddle(renderer);
	ball = new Ball(renderer);
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
