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

	void update(float delta) override;
	void render() override;
	void enter() override;
	void exit() override;
	void keyUp(SDL_KeyboardEvent& event) override;
	void keyDown(SDL_KeyboardEvent& event) override;

private:
	SDL_Texture* mExitText;
	SDL_Texture* mExitTextSelected;
	SDL_Texture* mHighscoresText;
	SDL_Texture* mHighscoresTextSelected;
	SDL_Texture* mPlayText;
	SDL_Texture* mPlayTextSelected;

	SDL_Texture* mLogo;

	SDL_Rect mExitTextPosition;
	SDL_Rect mHighscoresTextPosition;
	SDL_Rect mPlayTextPosition;
	SDL_Rect mLogoPosition;
	void executeMenu(int selected);
	int selectedItem{ 0 };
};




