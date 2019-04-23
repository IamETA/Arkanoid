#include "SDL.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>
#include <memory>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600

int main(int argc, char* argv[])
{
	std::unique_ptr<Game> game(new Game());

	const std::string fontPath = ".\\fonts\\default.ttf";

	//initialize game
	if (game->init_window( "Arkanoid",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_HEIGHT, SCREEN_WIDTH, false)
		&& game->init_font(fontPath))
	{
		game->run();
	}

	//input->Release();

	return 0;
}
