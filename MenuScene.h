#pragma once

#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"

class MenuScene final : public Scene
{
public:
	MenuScene(Game& game);

	~MenuScene();

	void update(float delta) override;
	void render() override;
	void enter() override;
	void exit() override;
	void keyUp(SDL_KeyboardEvent& event) override;
	void keyDown(SDL_KeyboardEvent& event) override;
private:
	SDL_Texture* mExitText{ nullptr };
	SDL_Texture* mExitTextSelected{ nullptr };
	SDL_Texture* mHighscoresText{ nullptr };
	SDL_Texture* mHighscoresTextSelected{ nullptr };
	SDL_Texture* mPlayText{ nullptr };
	SDL_Texture* mPlayTextSelected{ nullptr };

	SDL_Texture* mLogo;

	SDL_Rect mExitTextPosition{ 0,0,0,0 };
	SDL_Rect mHighscoresTextPosition{ 0,0,0,0 };
	SDL_Rect mPlayTextPosition{ 0,0,0,0 };
	SDL_Rect mLogoPosition{ 0,0,0,0 };


	void executeMenu(int selected);
	int selectedItem{ 0 };
};
