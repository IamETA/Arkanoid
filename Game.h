//
// Created by mynewdog on 11.03.19.
//

#ifndef ARCADEGAME_GAME_H
#define ARCADEGAME_GAME_H


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Timer.h"
#include "Scene.h"

namespace Game {

    class Game {
    public:
        explicit Game();
        ~Game();
        void handle_exit_event();
        bool init_window(const char *title, int xpos, int ypos, int height, int width, bool fullscreen);
		void update(unsigned int delta);
        void render(unsigned int delta);
		void run();
        bool running() { return game_running; }
		void enterScene(std::shared_ptr<Scene> scene);

	private:
		SDL_Window* window{ nullptr };
		SDL_Renderer* renderer{ nullptr };
		SDL_Event event{ NULL };
		std::shared_ptr<Scene> mScene{ nullptr };
		//Use chronos to keep track of time
		TimerUtils::Timer *timer;

		//Other definitions
		bool game_running{};
		int counter{ 0 };
    };
}


#endif //ARCADEGAME_GAME_H
