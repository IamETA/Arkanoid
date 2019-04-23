//
// Created by mynewdog on 11.03.19.
//

#include <iostream>
#include <cstdlib>
#include "Game.h"
#include <iostream>
#include "Scene.h"
#include "MenuScene.h"

SDL_Texture* playerTexture;
SDL_Texture* enemyTexture;
SDL_Rect srcR, destR;

namespace Game {

	Game::Game() {};

	Game::~Game() {
		
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		std::cout << "Game cleaned" << std::endl;
	};
	void Game::run() {
		timer = TimerUtils::Timer::Instance();
		timer->Reset();
		float fps{ 0 };
		int framecount{ 0 };
		/*
		unsigned int lasttick = SDL_GetTicks();
		// Calculate delta and fps
		unsigned int curtick = SDL_GetTicks();
		float delta = (curtick - lasttick) / 1000.0f;

		Gamle stabile måten:
		while (game_running)
		{
			handle_exit_event();
			// Calculate delta and fps
			unsigned int curtick = SDL_GetTicks();
			float delta = (curtick - lasttick) / 1000.0f;
			if (curtick - fpstick >= FPS_DELAY) {
				fps = framecount * (1000.0f / (curtick - fpstick));
				fpstick = curtick;
				framecount = 0;
				//std::cout << "FPS: " << fps << std::endl;
				char buf[100];
				snprintf(buf, 100, "Arkanoid copy (fps: %u)", fps);
				SDL_SetWindowTitle(window, buf);
			}
			else {
				framecount++;
			}
			lasttick = curtick;

			// Update and render the game
			update(delta);
			render(delta)
		}*/
	

		// set the initial scene for the game.
		enterScene(std::make_shared<MenuScene>(*this));

		while (game_running) {
			timer->Tick();
			//if (timer->delta_time() >= 1 / timer->get_frame_rate())
			//{
			if (timer->Delay() >= 500) {
				timer->Reset();
				framecount = 0;
				handle_exit_event();
				update(timer->delta_time());
				render(timer->delta_time());
			}
			else {
				framecount++;	
			}
			
			//}
		}
		timer->Release();
	}
	bool Game::init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
	{
		Uint32 flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
		{
			std::cout << "Subsystem initialized" << std::endl;
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (window) 
			{
				std::cout << "Window created" << std::endl;
			}
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer) 
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created" << std::endl;
			}
			game_running = true;
		}
		else 
		{
			std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
			game_running = false;
		}
		return game_running;
	}

	void Game::handle_exit_event() 
	{
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			game_running = false;
			break;

		default:
			break;
		}
	}


	void Game::update(unsigned int delta)
	{

		/*
		
		Foreløpig dette som gjør at bildet nå flytter på seg...
		
		*/
		counter++;
		destR.w = 64;
		destR.h = 64;
		destR.x = counter;


	}


	void Game::render(usigned int delta) 
	{
		SDL_RenderClear(renderer);

		/*This is where to  add stuff to render.
		First to get rendered is the background, then whatever comes after will be rendered on top*/
		playerTexture = TextureUtils::TextureManager::load_texture("textures/paddlev.png", renderer);
		SDL_RenderCopy(renderer, playerTexture, NULL, &destR);
		// --- End of rendering textures ------


		SDL_RenderPresent(renderer);

	}

	void Game::enterScene(std::shared_ptr<Scene> scene)
	{
		if (scene) {
			// perform a cleanup from the old scene (if any).
			if (mScene) {
				mScene->exit();
			}

			// apply the new scene and call the scene init (reset).
			mScene = scene;
			mScene->enter();
		}
	}


}