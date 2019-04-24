#pragma once

#include <iostream>
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
	Ball* ball{ nullptr };
	Level* level{ nullptr };
	Paddle* paddle{ nullptr };

public:
	GameScene(Game& game);
	~GameScene();

	void update(unsigned int dt) override;
	void render() override;
	void enter() override;
	void exit() override;
	void mouseEvent(SDL_MouseButtonEvent& event) override;
	void keyUp(SDL_KeyboardEvent& event) override;
	void keyDown(SDL_KeyboardEvent& event) override;
};

