#ifndef GAME_H_
#define GAME_H_

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <stdio.h>

#include "Level.h"
#include "Player.h"
#include "Ball.h"

#define FPS_DELAY 500

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Run();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* texture;

	// Timing
	unsigned int lasttick, fpstick, fps, framecount;

	// Test
	float testx, testy;

	int round = 0;
	Level* level;
	Player* player;
	Ball* ball;
	bool paddlestick;

	void Clean();
	void Update(float delta);
	void Render(float delta);

	void NewGame();
	void ResetPlayer();
	void StickBall();

	void SetPlayerX(float x);
	void CheckBoardCollisions();
	float GetReflection(float hitx);
	void CheckPaddleCollisions();
	void CheckBrickCollisions();
	void CheckBrickCollisions2();
	void BallBrickResponse(int dirindex);
	int GetBrickCount();
};

#endif