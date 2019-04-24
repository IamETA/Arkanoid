#ifndef ARCADEGAME_GAME_H
#define ARCADEGAME_GAME_H


#include <iosfwd>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Timer.h"
#include "Scene.h"

class Game {
private:

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	SDL_Event event{ NULL };
	std::shared_ptr<Scene> mScene{ nullptr };
	TextureManager* textureManager{ nullptr };
	//Use chronos to keep track of time
	TimerUtils::Timer *timer;
	TTF_Font*  mFont{ nullptr };

	//Game definitions

	//Other definitions
	bool game_running{};
	int counter{ 0 };

public:
	Game();
	~Game();
	void handle_exit_event();
	bool init_window(const char *title, int xpos, int ypos, int height, int width, bool fullscreen);
	bool init_font(const std::string fontPath);
	void update(unsigned int delta);
	void render();
	void run();
	bool running() { return game_running; }
	void enterScene(std::shared_ptr<Scene> scene);
	SDL_Renderer* getRenderer();
	TTF_Font* getFont();
	SDL_Window* getWindow();
};



#endif //ARCADEGAME_GAME_H
