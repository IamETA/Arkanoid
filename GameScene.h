#pragma once

#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
#include "Paddle.h"

class GameScene final : public Scene
{
private:
	int Life{ 3 };

	std::unique_ptr<Paddle> paddle;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Level> level;


public:
	GameScene(Game& game);
	~GameScene();

	void update(float dt) override;
	void render() override;
	void enter() override;
	void exit() override;
};

