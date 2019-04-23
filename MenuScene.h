#pragma once

#include "scene.h"
#include "Game.h"
#include <SDL.h>
namespace Game
{
	class MenuScene final : public Scene
	{
	public:
		MenuScene(Game& game);

		~MenuScene();

		void update(float dt) override;
		void render() override;
		void enter() override;
		void exit() override;
		void KeyEnter(SDL_KeyboardEvent& event);
		void keyUp(SDL_KeyboardEvent& event);
		void keyDown(SDL_KeyboardEvent& event);
	private:
		SDL_Texture* mExitText;
		SDL_Texture* mHighscoresText;
		SDL_Texture* mPlayText;

		SDL_Rect mExitTextPosition;
		SDL_Rect mHighscoresTextPosition;
		SDL_Rect mPlayTextPosition;
	};
}
