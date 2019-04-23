#pragma once

#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
namespace Game {
	class GameScene final : public Scene
	{
	private:
		Ball* ball{ nullptr };
		Ball* ball{ nullptr };
		Ball* ball{ nullptr };

	public:
		GameScene(Game& game);
		~GameScene();

		void update(float dt) override;
		void render() override;
		void enter() override;
		void exit() override;
	};

}
