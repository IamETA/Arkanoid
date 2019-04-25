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
	void key_up(SDL_KeyboardEvent& event) override;
	void key_down(SDL_KeyboardEvent& event) override;
private:
	SDL_Texture* m_exit_text{ nullptr };
	SDL_Texture* m_exit_text_selected{ nullptr };
	SDL_Texture* m_highscores_text{ nullptr };
	SDL_Texture* m_highscore_text_selected{ nullptr };
	SDL_Texture* m_play_text{ nullptr };
	SDL_Texture* m_play_text_selected{ nullptr };

	SDL_Texture* m_logo;

	SDL_Rect m_exit_text_pos{ 0,0,0,0 };
	SDL_Rect m_highscore_text_pos{ 0,0,0,0 };
	SDL_Rect m_play_text_pos{ 0,0,0,0 };
	SDL_Rect m_logo_pos{ 0,0,0,0 };


	void execute_menu(int selected);
	int selected_item{ 0 };
};
