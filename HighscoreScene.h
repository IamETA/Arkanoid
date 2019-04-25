#pragma once
#include "Scene.h"
#include "Highscores.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL.h>

class HighscoreScene :
	public Scene
{
public:
	HighscoreScene(Game& game);
	~HighscoreScene();

	void updateHighscore();
	void render() override;
	void enter() override;
	void exit() override;
	void keyUp(SDL_KeyboardEvent& event) override;
	void keyDown(SDL_KeyboardEvent& event) override;

private:
	SDL_Texture* mHighscoresText{ nullptr };
	SDL_Texture* mScoreText{ nullptr };
	Highscores* highscore{ nullptr };

	SDL_Texture* mLogo{ nullptr };

	SDL_Rect mExitTextPosition{ 0,0,0,0 };
	SDL_Rect mHighscoresTextPosition{ 0,0,0,0 };
	SDL_Rect mPlayTextPosition{ 0,0,0,0 };
	SDL_Rect mLogoPosition{ 0,0,0,0 };
};




