#pragma once
#include "Level.h"
#include <iostream>

Level::Level(SDL_Renderer* renderer) : GameObject(".\\textures\\bricks.png",renderer) 
{
	// Endre til mer dynamisk bricks, med background color
	bricktexture = m_object_texture;

	SDL_Surface* surface = IMG_Load(".\\textures\\purple_side.png");
	sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srand(time(0));

	brick_offset_x = 16;
	brick_offset_y = 10;
	x = 0;
	y = 0;
	width = 800 - brick_offset_x;
	height = 600;

}

Level::~Level()
{
	// Clean resources
	SDL_DestroyTexture(sidetexture);
}

void Level::update(float delta)
{

}

void Level::render() {
	// Render bricks
	for (int i = 0; i < LEVEL_WIDTH; i++)
	{
		for (int j = 0; j < LEVEL_HEIGHT; j++)
		{
			Brick brick = bricks[i][j];

			// Check if the brick exists
			if (!brick.state)
				continue;

			SDL_Rect srcrect;

			srcrect.x = (brick.type % 2) * LEVEL_BRWIDTH;
			srcrect.y = (brick.type / 2) * LEVEL_BRHEIGHT;
			srcrect.w = LEVEL_BRWIDTH;
			srcrect.h = LEVEL_BRHEIGHT;

			SDL_Rect dstrect;
			dstrect.x = brick_offset_x + x + i * LEVEL_BRWIDTH;
			dstrect.y = brick_offset_y + y + j * LEVEL_BRHEIGHT;
			dstrect.w = LEVEL_BRWIDTH;
			dstrect.h = LEVEL_BRHEIGHT;

			SDL_RenderCopy(m_renderer, bricktexture, &srcrect, &dstrect);
		}
	}

	// Render sides
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(m_renderer, sidetexture, 0, &dstrect);

	dstrect.x = 800 - 16;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(m_renderer, sidetexture, 0, &dstrect);
}

void Level::next_level(int round) 
{
	if (round == 1) 
	{
		create_round_one();
	}
	if (round == 2)
	{
		create_round_two();
	}
	if (round == 3)
	{
		create_round_three();
	}
	
}
// Rainbow with tiered hit points bricks
void Level::create_round_one()
{
	std::cout << "Level 1" << std::endl;
	for (int i = 1; i < LEVEL_WIDTH; i++)
	{
		for (int j = 1; j < LEVEL_HEIGHT; j++)
		{
			if (j <= 5) 
			{
				Brick brick;
				brick.type = 0; 
				brick.state = false; // empty
				brick.hp = 0;
				bricks[i][j] = brick;
			}
			if (j == 6) 
			{
				Brick brick;
				brick.type = 3; // blue
				brick.state = true;
				brick.hp = 3;
				bricks[i][j] = brick;
			}
			if (j == 7) 
			{
				Brick brick;
				brick.type = 2; // green
				brick.state = true;
				brick.hp = 2;
				bricks[i][j] = brick;
			}
			if (j == 8)
			{
				Brick brick;
				brick.type = 1; // yellow
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}
			if (j == 9) 
			{
				Brick brick;
				brick.type = 0; // red
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
		}
	}
}
// Swedish flag
void Level::create_round_two() 
{
	for (int i = 1; i < LEVEL_WIDTH; i++) 
	{
		for (int j = 1; j < LEVEL_HEIGHT; j++) 
		{

			if (i == 4 || j == 5) 
			{
				Brick brick;

				brick.type = 1; // yellow
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}
			if (i != 4 && j != 5) {
				Brick brick;
				brick.type = 3; // blue
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
		}
	}
}
// U shape with indestructible bricks
void Level::create_round_three() 
{
	for (int i = 1; i < LEVEL_WIDTH; i++) 
	{
		for (int j = 1; j < LEVEL_HEIGHT; j++) 
		{			
			if (i == 3 && j != 1 && j != 8 && j != 9 ) 
			{
				Brick brick;
				brick.type = 5; // grey
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			 else if (i == 8 && j != 1 && j != 8 && j != 9)
			{
				Brick brick;
				brick.type = 5; // grey
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			else if(j == 7 && i != 1 && i != 2 && i != 8 && i != 9) 
			{
				Brick brick;
				brick.type = 5; // grey
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			else 
			{
				Brick brick;
				brick.type = 4; // pink
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
		}
	}
}