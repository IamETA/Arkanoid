#include <iostream>
#include <cstdlib>
#include "Game.h"
#include <iostream>
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "InputManager.h"


Game::Game()
{
}

void Game::exit() {
	game_running = false;
}
Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Free music
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	std::cout << "Game destroyed" << std::endl;
};
void Game::run()
{
	InputUtils::InputManager* input = InputUtils::InputManager::Instance();

	//Use chronos time library to control updates
	timer = TimerUtils::Timer::Instance();
	timer->reset();
	float fps{ 0 };

	//Used to calculate fps
	int framecount{ 0 };

	// set the initial scene for the game.
	enter_scene(std::make_shared<MenuScene>(*this));

	//Play the music
	Mix_PlayMusic(music, -1);

	while (game_running) 
	{
		timer->tick();
		if (timer->delay() >= 100) 
		{
			input->update();
			timer->reset();
			framecount = 0;
			handle_input_event();
			update(timer->delta_time());

			//Debug delta time, remove later
			//std::cout << "Delta time: " << timer->delta_time() << "\r\n";


			render();
		}
		else {
			framecount++;
		}
	}
	timer->Release();
	input->Release();
}
bool Game::init_font(const std::string fontPath) {
	std::cout << "initializing fonts..." << std::endl;

	// initialize TTF system for text rendering.
	if (TTF_Init() == -1) 
	{
		std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
		return false;
	}


	// initialize the selected font for the application.
	m_font = TTF_OpenFont(fontPath.c_str(), 28);
	if (m_font == nullptr) 
	{
		std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Game::init_music()
{
	std::cout << "initializing audio..." << std::endl;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	music = Mix_LoadMUS(".\\sounds\\background.wav");
	if (music == NULL)
	{
		return false;
	}
	// Control the volume
	Mix_VolumeMusic(50);
	return true;
}

//initialize sdl window 
bool Game::init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	std::cout << "initializing main window..." << std::endl;
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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
void Game::handle_input_event()
{
	while (SDL_PollEvent(&event) != 0) 
	{
		switch (event.type) 
		{
		case SDL_QUIT:
			game_running = false;
			break;
		case SDL_KEYDOWN:
			if (m_scene)
			{
				m_scene->key_down(event.key);
			}
			break;
		case SDL_KEYUP:
			if (m_scene) 
			{
				m_scene->key_up(event.key);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (m_scene) 
			{
				m_scene->mouse_down(event.key);
			}
		default:
			break;
		}
	}
}


void Game::update(float delta)
{
	m_scene->update(delta);
}


void Game::render()
{
	SDL_RenderClear(renderer);
	if (m_scene != nullptr) 
	{
		m_scene->render();
	}
	SDL_RenderPresent(renderer);
}

void Game::enter_scene(std::shared_ptr<Scene> scene)
{
	if (scene) {
		// perform a cleanup from the old scene (if any).
		if (m_scene) 
		{
			m_scene->exit();
		}

		// apply the new scene and call the scene init (reset).
		m_scene = scene;
		m_scene->enter();
	}
}

SDL_Renderer* Game::get_renderer()
{
	return renderer;
}

TTF_Font* Game::get_font()
{
	return m_font;
}

SDL_Window* Game::get_window()
{
	return window;
}
