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
	//Free the music
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	std::cout << "Game destroyed" << std::endl;
};
void Game::run() 
{
	InputUtils::InputManager *input = InputUtils::InputManager::Instance();

	//Use chronos time library to control updates
	timer = TimerUtils::Timer::Instance();
	timer->Reset();
	float fps{ 0 };

	//Used to calculate fps
	int framecount{ 0 };

	// set the initial scene for the game.
	enterScene(std::make_shared<MenuScene>(*this));

	//Play the music
	Mix_PlayMusic(music, -1);
	
	while (game_running) {
		timer->Tick();
		if (timer->Delay() >= 100) {
			input->Update();
			timer->Reset();
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

	// initialize TTF system for text rendering.
	if (TTF_Init() == -1) {
		std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
		return false;
	}


	// initialize the selected font for the application.
	mFont = TTF_OpenFont(fontPath.c_str(), 28);
	if (mFont == nullptr) {
		std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Game::init_music()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	//Load the music
	music = Mix_LoadMUS(".\\sounds\\background.wav");


	//If there was a problem loading the music
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
			SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
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
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			game_running = false;
			break;
		case SDL_KEYDOWN:
			if (mScene) {
				mScene->keyDown(event.key);
			}
			break;
		case SDL_KEYUP:
			if (mScene) {
				mScene->keyUp(event.key);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mScene) {
				mScene->mouseDown(event.key);
			}
		default:
			break;
		}
	}
}


void Game::update(float delta)
{
	mScene->update(delta);
}


void Game::render()
{
	SDL_RenderClear(renderer);
	mScene->render();

	/*This is where to  add stuff to render.
	First to get rendered is the background, then whatever comes after will be rendered on top*/
	//playerTexture = TextureManager::load_texture("textures/paddlev.png", renderer);
	//SDL_RenderCopy(renderer, playerTexture, NULL, &destR);
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

SDL_Renderer * Game::getRenderer()
{
	return renderer;
}

TTF_Font * Game::getFont()
{
	return mFont;
}

SDL_Window * Game::getWindow()
{
	return window;
}
