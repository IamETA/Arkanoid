#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iosfwd>
#include <SDL_ttf.h>

namespace Game {
	class TextureManager final {

    public:
		explicit TextureManager();
		~TextureManager();
        static SDL_Texture *load_texture(std::string texture, SDL_Renderer *ren);
		SDL_Texture* CreateText(const std::string& text);

	private: 
		TTF_Font* mFont{ nullptr };
		SDL_Renderer* mRenderer{ nullptr };
    };
}