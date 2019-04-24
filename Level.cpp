#include "Level.h"

Level::Level(SDL_Renderer* renderer) : Item(renderer) {
	SDL_Surface* surface = IMG_Load("bricks.png"); // Endre til BMP fil
	bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("side.png"); // endre til BMP fil
	sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srand(time(0));

	x = 10;
	y = 10;
	width = 768;
	height = 600;

	brickoffsetx = 10;
	brickoffsety = 10;
}

Level::~Level() {
	// Clean resources
	SDL_DestroyTexture(bricktexture);
	SDL_DestroyTexture(sidetexture);
}

void Level::Update(float delta) {

}

void Level::Render(float delta) {
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

			SDL_RenderCopy(renderer, bricktexture, &srcrect, &dstrect);
		}
	}

	// Render Left side
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
	// Render Right side
	dstrect.x = 800 - 16;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
}

void Level::CreateLevel(int round) {
	if (round == 1) {
		CreateRound2();
	}
	if(round == 0) {
		CreateRound1();
	}
}

void Level::CreateRound1() {
	for (int i = 5; i < LEVEL_WIDTH; i++) {
		for (int j = 5; j < LEVEL_HEIGHT; j++) {
				Brick brick;
				brick.type = 2; // Example of a fixed pattern using xor red type 1 = yellow
				brick.state = true;         // Brick is present
				brick.HP = 0;
				bricks[i][j] = brick;
		}
	}
}

void Level::CreateRound2() {
	for (int i = 1; i < LEVEL_WIDTH; i++) {
		for (int j = 1; j < LEVEL_HEIGHT; j++) {

			if (i == 4) {
				Brick brick;

				brick.type = 3; // Example of a fixed pattern using xor red type 1 = yellow
				brick.state = true;         // Brick is present
				brick.HP = 1;
				bricks[i][j] = brick;
			}
			if (j == 5) {
				Brick brick;

				brick.type = 3; // Example of a fixed pattern using xor red type 1 = yellow
				brick.state = true;         // Brick is present
				brick.HP = 1;
				bricks[i][j] = brick;
			}
			if (i != 4 && j != 5 && i != 3 && j != 4 && i != 5 && j != 6) {
				Brick brick;
				brick.type = 0; // Example of a fixed pattern using xor blue
				brick.state = true;         // Brick is present
				brick.HP = 0;
				bricks[i][j] = brick;
			}
			/*if (i == 1 || i == LEVEL_WIDTH - 2 || j == 1 || j == LEVEL_HEIGHT - 2) {
				Brick brick;

				brick.type = 0; // Example of a fixed pattern using xor red type 1 = yellow
				brick.state = true;         // Brick is present
				brick.HP = 1;
				bricks[i][j] = brick;
			}
			else {
				Brick brick;
				brick.type = 2; // Example of a fixed pattern using xor green
				brick.state = true;         // Brick is present
				brick.HP = 0;
				bricks[i][j] = brick;
			}
			if (j == 9) {
				Brick brick;
				brick.type = 3; // Example of a fixed pattern using xor blue
				brick.state = true;         // Brick is present
				brick.HP = -1;
				bricks[i][j] = brick;
			}*/
		}
	}
}