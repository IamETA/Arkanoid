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
	void next_level(int round);
	void create_round_one();
	void create_round_two();
	void create_round_three();

	float brick_offset_x, brick_offset_y;

	// Define the two-dimensional array of bricks
	Brick bricks[LEVEL_WIDTH][LEVEL_HEIGHT];

private:
	SDL_Texture* bricktexture;
	SDL_Texture* sidetexture;
};

