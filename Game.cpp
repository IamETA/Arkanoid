//
// Created by mynewdog on 11.03.19.
//

#include <iostream>
#include "Game.h"
#include "TextureManager.h"

SDL_Texture *playerTexture;
SDL_Texture *enemyTexture;
SDL_Rect srcR, destR;

namespace Game {

Game::Game() {};

Game::~Game() {};

void Game::init_window(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    Uint32 flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystem initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        is_running = true;
    } else {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        is_running = false;
    }

}

void Game::handle_exit_event() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    counter++;
    destR.w = 64;
    destR.h = 64;
    destR.x = counter;


    std::cout << counter << std::endl;
}

void Game::render() {
    SDL_RenderClear(renderer);

    /*This is where to  add stuff to render.
    First to get rendered is the background, then whatever comes after will be rendered on top*/
    playerTexture = TextureUtils::TextureManager::load_texture("textures/mario.png", renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, &destR);
    // --- End of rendering textures ------

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
}