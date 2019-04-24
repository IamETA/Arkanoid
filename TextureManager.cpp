#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::load_texture(std::string texture, SDL_Renderer* ren)
{
	SDL_Surface* temp_surface = IMG_Load(texture.c_str());
	if (temp_surface == nullptr)
	{
		std::cout << "Unable to load image: " << SDL_GetError() << std::endl;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp_surface);
	SDL_FreeSurface(temp_surface);
	return tex;
}

SDL_Texture* TextureManager::create_text(const std::string& text, SDL_Renderer* ren, TTF_Font* font)
{
	SDL_Color color{ 0xff, 0xff, 0xff, 0xff };

}
SDL_Texture* TextureManager::create_text(const std::string& text, SDL_Renderer* ren, TTF_Font* font, SDL_Color color)
{
	// create a surface which contains the desired text.
	auto surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface == nullptr) {
		std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// create a texture from the text surface.
	auto texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	return texture;
}
