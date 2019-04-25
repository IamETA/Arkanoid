#pragma once

#include <iosfwd>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Timer.h"
#include "Scene.h"
#include "SDL_mixer.h"

class Game {
private:

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	SDL_Event event{ NULL };
	std::shared_ptr<Scene> m_scene{ nullptr };
	std::shared_ptr<Scene> m_high_scene{ nullptr };
	TextureManager* texture_manager{ nullptr };

	//Use chronos to keep track of time
	TimerUtils::Timer *timer;
	TTF_Font*  m_font{ nullptr };

	//Game definitions

	//Other definitions
	bool game_running{};
	int counter{ 0 };
	Mix_Music *music{ nullptr };

public:
	Game();
	~Game();
	void handle_input_event(); 
	bool init_window(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool init_font(const std::string fontPath);
	bool init_music();
	void update(float delta);
	void render();
	void run();
	void exit();
	bool running() { return game_running; }
	void enter_scene(std::shared_ptr<Scene> scene);
	SDL_Renderer* get_renderer();
	TTF_Font* get_font();
	SDL_Window* get_window();
};
