#pragma once
#include "Scene.h"
#include "Highscores.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

class HighscoreScene :
	public Scene
{
public:
	HighscoreScene(Game& game);
	~HighscoreScene();

	void update_highscore();
	void render() override;
	void enter() override;
	void exit() override;
	void key_up(SDL_KeyboardEvent& event) override;
	void key_down(SDL_KeyboardEvent& event) override;

private:
	std::string highscore_string{""};
	SDL_Texture* m_highscores_text{ nullptr };
	SDL_Texture* m_score_text{ nullptr };
	Highscores* highscore{ nullptr };
	SDL_Texture* m_logo{ nullptr };
	SDL_Rect m_highscore_text_pos{ 0,0,0,0 };
	SDL_Rect m_logo_pos{ 0,0,0,0 };
};




