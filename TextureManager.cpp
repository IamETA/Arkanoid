//
// Created by mynewdog on 11.03.19.
//

#include "TextureManager.h"
#include <iostream>



SDL_Texture* TextureUtils::TextureManager::load_texture(std::string texture, SDL_Renderer *ren) {
    SDL_Surface* temp_surface = IMG_Load(texture.c_str());
    if(temp_surface == nullptr) {
        std::cout << "Unable to load image: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp_surface);
    SDL_FreeSurface(temp_surface);
    return tex;
}