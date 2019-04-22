#include "Level.h"

Level::Level(SDL_Renderer* renderer) : Entity(renderer) {
	SDL_Surface* surface = IMG_Load("bricks.png"); // Endre til BMP fil
	bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("side.png"); // endre til BMP fil
	sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srand(time(0));

	x = 16;
	y = 0;
	width = 768;
	height = 600;

	brickoffsetx = 0;
	brickoffsety = 16;
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
	for (int i = 0; i < Level_WIDTH; i++) {
		for (int j = 0; j < Level_HEIGHT; j++) {
			Brick brick = bricks[i][j];

			// Check if the brick exists
			if (!brick.state)
				continue;

			SDL_Rect srcrect;

			srcrect.x = (brick.type % 2) * Level_BRWIDTH;
			srcrect.y = (brick.type / 2) * Level_BRHEIGHT;
			srcrect.w = Level_BRWIDTH;
			srcrect.h = Level_BRHEIGHT;

			SDL_Rect dstrect;
			dstrect.x = brickoffsetx + x + i * Level_BRWIDTH;
			dstrect.y = brickoffsety + y + j * Level_BRHEIGHT;
			dstrect.w = Level_BRWIDTH;
			dstrect.h = Level_BRHEIGHT;

			SDL_RenderCopy(renderer, bricktexture, &srcrect, &dstrect);
		}
	}

	// Render sides
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);

	dstrect.x = 800 - 16;
	dstrect.y = 0;
	dstrect.w = 16;
	dstrect.h = 600;
	SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
}

void Level::CreateLevel() {
	for (int i = 0; i < Level_WIDTH; i++) {
		for (int j = 0; j < Level_HEIGHT; j++) {
			Brick brick;

			//brick.type = rand() % 4;    // Random color
			brick.type = (i ^ j) % 4; // Example of a fixed pattern using xor
			brick.state = true;         // Brick is present
			bricks[i][j] = brick;
		}
	}
}