#pragma once
/*! An abstraction for all scenes in the Arkanoid game.
 *
 *  This class acts as an abstraction for all scenes in our Breakout game. Our
 *  implementation contains only two different scenes that inherit from this
 *  base class. Scenes also act as a high abstraction game states, which have a
 *  enter and exit functionality that is executed automatically when the scene
 *  is being entered or exited from.
 */

 // global namespace forward declarations.
struct SDL_KeyboardEvent;

namespace Game
{
	class Game;
	class Scene
	{
	public:
		Scene(Game& game) : mGame(game) {}

		virtual ~Scene() = default;

		virtual void update(float dt) {}
		virtual void render() {}
		virtual void enter() {}
		virtual void exit() {}
		virtual void keyDown(SDL_KeyboardEvent& event) {}
		virtual void keyUp(SDL_KeyboardEvent& event) {}
	protected:
		Game& mGame;
	};
}