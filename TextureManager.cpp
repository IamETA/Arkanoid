//
// Created by mynewdog on 11.03.19.
//

#include "TextureManager.h"
#include <iostream>
#include <SDL_ttf.h>

namespace TextureUtils {

	TextureManager::TextureManager() {
			// initialize TTF system for text rendering.
		if (TTF_Init() == -1) {
		  std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
		  return;
		}

		const std::string fontPath = ".\\fonts\\default.ttf";

		// initialize the selected font for the application.
		mFont = TTF_OpenFont(fontPath.c_str(), 28);
		if (mFont == nullptr) {
			std::cerr << "Unable to load font: " << TTF_GetError() << std::endl;
			return;
		}
	}
	
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

	SDL_Texture* TextureManager::createText(const std::string& text)
	{
		// create a surface which contains the desired text.
		SDL_Color color{ 0xff, 0xff, 0xff, 0xff };
		auto surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
		if (surface == nullptr) {
			std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
			return nullptr;
		}

		// create a texture from the text surface.
		auto texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) {
			std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		return texture;
	}

}