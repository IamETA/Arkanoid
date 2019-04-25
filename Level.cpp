#pragma once
#include "Level.h"

Level::Level(SDL_Renderer* renderer) : GameObject(".\\textures\\bricks.png",renderer) {
	// Endre til mer dynamisk bricks, med background color
	SDL_Surface* surface = IMG_Load(".\\textures\\bricks.png");
	bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load(".\\textures\\purple_side.png");
	sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srand(time(0));

	brickoffsetx = 16;
	brickoffsety = 10;
	x = 0;
	y = 0;
	width = 800 - brickoffsetx;
	height = 600;

}

Level::~Level() {
	// Clean resources
	SDL_DestroyTexture(bricktexture);
	SDL_DestroyTexture(sidetexture);
}

void Level::update(float delta) {

}

void Level::render() {
	// Render bricks
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
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
			dstrect.x = brickoffsetx + x + i * LEVEL_BRWIDTH;
			dstrect.y = brickoffsety + y + j * LEVEL_BRHEIGHT;
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

void Level::NextLevel(int round) {
	if (round == 1) {
		CreateRound1();
	}
	if (round == 2) {
		CreateRound2();
	}
	if (round == 3) {
		CreateRound3();
	}
	
}
// Rainbow
void Level::CreateRound1() {
	for (int i = 1; i < LEVEL_WIDTH+1; i++) {
		for (int j = 6; j < LEVEL_HEIGHT; j++) {
			if (j == 6) {
				Brick brick;
				brick.type = 3; // blue
				brick.state = true;
				brick.hp = 3;
				bricks[i][j] = brick;
			}
			if (j == 7) {
				Brick brick;
				brick.type = 2; // green
				brick.state = true;
				brick.hp = 2;
				bricks[i][j] = brick;
			}
			if (j == 8) {
				Brick brick;
				brick.type = 1; // yellow
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}
			if (j == 9) {
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
void Level::CreateRound2() {
	for (int i = 1; i < LEVEL_WIDTH; i++) {
		for (int j = 1; j < LEVEL_HEIGHT; j++) {

			if (i == 4 || j == 5) {
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
// Steps with industritible(spell?) NOT DONE
void Level::CreateRound3() {
	for (int i = 1; i < LEVEL_WIDTH; i++) {
		for (int j = 1; j < LEVEL_HEIGHT; j++) {

			/*if (j != 9 && i != 5) {
				Brick brick;

				brick.type = 0; // red
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}*/
			
			if (i == 3 && j != 1 && j != 8 && j != 9 ) {
				Brick brick;
				brick.type = 5; // grey (j != 2 || j != 3 || j != 8 || j != 9)
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			 else if (i == 8 && j != 1 && j != 8 && j != 9) {
				Brick brick;
				brick.type = 5; // grey (j != 2 || j != 3 || j != 8 || j != 9)
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			else if(j == 7 && i != 1 && i != 2 && i != 8 && i != 9) {
				Brick brick;
				brick.type = 5; // grey (i != 2 || i != 3 || i != 8 || i != 9)
				brick.state = true;
				brick.hp = -1; // indestructible
				bricks[i][j] = brick;
			}
			else {
				Brick brick;
				brick.type = 4; // pink
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
		}
	}
}