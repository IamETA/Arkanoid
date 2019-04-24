#pragma once

#include <iostream>
#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
#include "Paddle.h"

class GameScene final : public Scene
{
private:
	int Life{ 3 };

	Paddle* paddle;
	Ball* ball;
	Level* level;
	InputUtils::InputManager*  input{ nullptr };

	SDL_Texture* mLivesText{ nullptr };
	SDL_Texture* mScoreText{ nullptr };
	SDL_Texture* mDifficulty{ nullptr };
	SDL_Texture* mLevel{ nullptr };
	SDL_Texture* mLogo{ nunullptr };

	SDL_Rect mLivesPosition{ nullptr };
	SDL_Rect mScoreTextPosition{ nullptr };
	SDL_Rect mDifficultyPosition{ nullptr };
	SDL_Rect mLevelPosition{ nullptr };
	SDL_Rect mLogoPosition{ nullptr };

	void UpdatePaddlePosition();
	void UpdateBallCheckReleased();
	void UpdateMapCollisionDetection();
	void UpdatePaddleCollisionDetection();
	void UpdateLevelCollisionDetection();

public:
	GameScene(Game& game);
	~GameScene();

	void update(float delta) override;
	void render() override;
	void enter() override;
	void exit() override;
	void keyUp(SDL_KeyboardEvent & event) override;
	void keyDown(SDL_KeyboardEvent & event) override;
	void mouseDown(SDL_KeyboardEvent & event) override;

	float GetReflection(float hitx); 
	void BallBrickResponse(int dirindex);
	void ResetBall();
};

