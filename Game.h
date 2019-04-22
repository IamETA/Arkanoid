//
// Created by mynewdog on 11.03.19.
//

#ifndef ARCADEGAME_GAME_H
#define ARCADEGAME_GAME_H


#include <SDL.h>
#include <SDL_image.h>
#include <iosfwd>

namespace Game {

    class Game {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        bool is_running;
        int counter{0};

    public:
        explicit Game();

        ~Game();

        void handle_exit_event();

        void init_window(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

        void update();

        void render();

        void clean();

        bool running() { return is_running; }

    };
}


#endif //ARCADEGAME_GAME_H
