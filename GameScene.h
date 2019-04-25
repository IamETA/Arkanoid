#pragma once

#include <iostream>
#include "scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "SDL_mixer.h"
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
#include "Paddle.h"
#include "Highscores.h"

enum brick_hit_face { top, bottom, left, right };

class GameScene final : public Scene
{
private:
	const int stats_left_margin{ 60 };
	const int stats_height_margin{ 70 };


	int Life{ 3 };
	int CurrentLevel{ 3 };
	int Score{ 0 };
	int Difficulty{ 1 };

	bool move_left{ false };
	bool move_right{ false };

	Paddle* paddle;
	Ball* ball;
	Level* level;
	Highscores* highscore;
	InputUtils::InputManager*  input{ nullptr };

	SDL_Texture* mLivesText{ nullptr };
	SDL_Texture* mScoreText{ nullptr };
	SDL_Texture* mDifficultyText{ nullptr };
	SDL_Texture* mLevelText{ nullptr };
	SDL_Texture* mLogo{ nullptr };

	SDL_Rect mLivesTextPosition{ 0,0,0,0 };
	SDL_Rect mScoreTextPosition{ 0,0,0,0 };
	SDL_Rect mDifficultyTextPosition{ 0,0,0,0 };
	SDL_Rect mLevelTextPosition{ 0,0,0,0 };
	SDL_Rect mLogoPosition{ 0,0,0,0 };

	void update_stats_lives();
	void update_stats_score();
	void update_stats_difficulty();
	void update_stats_level();
	void update_logo();


	void UpdatePaddlePosition();
	void UpdateBallCheckReleased();
	void UpdateMapCollisionDetection();
	void UpdatePaddleCollisionDetection();
	void UpdateLevelCollisionDetectionMove();
	int GetBrickNum();
	void LevelUp();

	//The sound effects that will be used
	Mix_Chunk *cPaddle{ NULL };
	Mix_Chunk *cBrick{ NULL };
	Mix_Chunk *cBottom{ NULL };
	Mix_Chunk *cSides{ NULL };
	Mix_Chunk *cNextRound{ NULL };
	Mix_Chunk *cGameOver{ NULL };

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
	void brick_hit(brick_hit_face face);
	void ResetBall();

};

