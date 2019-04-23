#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iosfwd>
#include <SDL_ttf.h>

class TextureManager final {

public:
	~TextureManager();
    static SDL_Texture* load_texture(std::string texture, SDL_Renderer *ren); 
	static SDL_Texture* create_text(const std::string& text, SDL_Renderer* ren, TTF_Font* font);

};
