#pragma once

// Abstract class for all game scenes

struct SDL_KeyboardEvent;

class Game;
class Scene
{
	public:
		Scene(Game& game) : mGame(game) {};

		virtual ~Scene() = default;

		virtual void update(float delta) {}
		virtual void render() {}
		virtual void enter() {}
		virtual void exit() {}
		virtual void key_down(SDL_KeyboardEvent& event) {}
		virtual void key_up(SDL_KeyboardEvent& event) {}
		virtual void mouse_down(SDL_KeyboardEvent& event) {}
	protected:
		Game& mGame;
};
