#pragma once

#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
#include "Paddle.h"

namespace Game {
	class GameScene final : public Scene
	{
	private:
		int Life { 3 }
		Ball* ball{ nullptr };
		Level* level{ nullptr };
		Paddle* paddle{ nullptr };

	public:
		GameScene(Game& game);
		~GameScene();

		void update(float dt) override;
		void render() override;
		void enter() override;
		void exit() override;
	};

}
