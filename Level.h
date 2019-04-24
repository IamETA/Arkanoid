#pragma once
#include "GameObject.h"
#include <stdlib.h>
#include <time.h>

// Define the dimensions of the level and bricks
#define LEVEL_WIDTH 10
#define LEVEL_HEIGHT 10
#define LEVEL_BRWIDTH 64
#define LEVEL_BRHEIGHT 24

class Brick {
public:
	int type;
	bool state;
	int hp;
};

class Level : public GameObject {
public:
	Level(SDL_Renderer* renderer);
	~Level();

	void update(float delta) override;
	void render() override;
	void NextLevel(int round);
	void CreateRound1();
	void CreateRound2();
	void CreateRound3();

	float brickoffsetx, brickoffsety;

	// Define the two-dimensional array of bricks
	Brick bricks[LEVEL_WIDTH][LEVEL_HEIGHT];

private:
	SDL_Texture* bricktexture;
	SDL_Texture* sidetexture;
};

