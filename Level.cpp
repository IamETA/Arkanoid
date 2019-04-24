#pragma once
#include "Level.h"

Level::Level(SDL_Renderer* renderer) : GameObject(".\\textures\\bricks.png",renderer) {
	// Endre til mer dynamisk bricks, med background color
	SDL_Surface* surface = IMG_Load(".\\textures\\bricks.png");
	bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load(".\\textures\\side.png");
	sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srand(time(0));

	x = 0;
	y = 0;
	width = 768;
	height = 600;

	brickoffsetx = 0;
	brickoffsety = 10;
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

void Level::CreateRound1() {
	for (int i = 5; i < LEVEL_WIDTH; i++) {
		for (int j = 5; j < LEVEL_HEIGHT; j++) {

			if (i == 1 || i == LEVEL_WIDTH - 2 || j == 1 || j == LEVEL_HEIGHT - 2) {
				Brick brick;

				brick.type = 0;
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}
			else {
				Brick brick;
				brick.type = 2;
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
		}
	}
}

void Level::CreateRound2() {
	for (int i = 1; i < LEVEL_WIDTH; i++) {
		for (int j = 1; j < LEVEL_HEIGHT; j++) {

			if (i == 1 || i == LEVEL_WIDTH - 2 || j == 1 || j == LEVEL_HEIGHT - 2) {
				Brick brick;

				brick.type = 0;
				brick.state = true;
				brick.hp = 1;
				bricks[i][j] = brick;
			}
			else {
				Brick brick;
				brick.type = 2;
				brick.state = true;
				brick.hp = 0;
				bricks[i][j] = brick;
			}
			if (j == 9) {
				Brick brick;
				brick.type = 3;
				brick.state = true;
				brick.hp = -1;
				bricks[i][j] = brick;
			}
		}
	}
}