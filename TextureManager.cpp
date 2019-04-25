#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::load_texture(std::string texture, SDL_Renderer* ren)
{
	SDL_Surface* temp_surface = IMG_Load(texture.c_str());	
	
	//Uint32 colorkey = SDL_MapRGB(temp_surface->format, 255, 255, 0);
	//SDL_SetColorKey(temp_surface, SDL_TRUE, colorkey);
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
	//Default color: White
	SDL_Color color{ 0xff, 0xff, 0xff, 0xff };
	return create_text(text, ren, font, color);
}
//Custom color function for text surfaces
SDL_Texture* TextureManager::create_text(const std::string& text, SDL_Renderer* ren, TTF_Font* font, SDL_Color color)
{
	// create a surface which contains the desired text.
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface == nullptr) {
		std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// create a texture from the text surface.
	SDL_Texture*  texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	return texture;
}

TextureManager::~TextureManager() {
	std::cout << "Texture destroyed" << std::endl;
}
