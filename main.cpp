#include "SDL.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>
#include <memory>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 1100

#if(_DEBUG) 
int main(int argc, char* argv[])
{
	std::unique_ptr<Game> game(new Game());

	const std::string fontPath = ".\\fonts\\arcade.ttf";

	//initialize game --> Set last flag to true if you want fullscreen
	if (game->init_window("Arkanoid",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, false)
		&& game->init_font(fontPath)
		&& game->init_music())
	{
		game->run();
	}

	return 0;
}
#else
int WinMain()
{
	std::unique_ptr<Game> game(new Game());

	const std::string fontPath = ".\\fonts\\arcade.ttf";

	//initialize game --> Set last flag to true if you want fullscreen
	if (game->init_window("Arkanoid",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, false)
		&& game->init_font(fontPath)
		&& game->init_music())
	{
		game->run();
	}

	return 0;
}
#endif

