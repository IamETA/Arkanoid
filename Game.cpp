#include "Game.h"

Game::Game() {
	window = 0;
	renderer = 0;
}

Game::~Game() {

}

bool Game::Init() {
	SDL_Init(SDL_INIT_VIDEO);

	// Create window
	window = SDL_CreateWindow("Arkanoid copy",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "Error creating window:" << SDL_GetError() << std::endl;
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer:" << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize resources
	SDL_Surface* surface = IMG_Load("test.png"); // endre til bmp fil.
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Initialize timing
	lasttick = SDL_GetTicks();
	fpstick = lasttick;
	fps = 0;
	framecount = 0;

	testx = 0;
	testy = 0;

	return true;
}

void Game::Clean() {
	// Clean resources
	SDL_DestroyTexture(texture);

	// Clean renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Run() {
	level = new Level(renderer);
	player = new Player(renderer);
	ball = new Ball(renderer);

	NewGame();

	while (1) {
		// Handler events 
		// TODO:: Add quit via menu with "esc"
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		// Calculate delta and fps
		unsigned int curtick = SDL_GetTicks();
		float delta = (curtick - lasttick) / 1000.0f;
		if (curtick - fpstick >= FPS_DELAY) {
			fps = framecount * (1000.0f / (curtick - fpstick));
			fpstick = curtick;
			framecount = 0;
			//std::cout << "FPS: " << fps << std::endl;
			char buf[100];
			snprintf(buf, 100, "Arkanoid copy (fps: %u)", fps);
			SDL_SetWindowTitle(window, buf);
		}
		else {
			framecount++;
		}
		lasttick = curtick;

		// Update and render the game
		Update(delta);
		Render(delta);
	}

	delete level;
	delete player;
	delete ball;

	Clean();

	SDL_Quit();
}

void Game::NewGame() {
	level->CreateLevel();
	ResetPlayer();
}

void Game::ResetPlayer() {
	paddlestick = true;
	StickBall();
}

void Game::StickBall() {
	ball->x = player->x + player->width / 2 - ball->width / 2;
	ball->y = player->y - ball->height;
}

void Game::Update(float delta) {

	// Input TODO:: move to inputmanager class
	int mx, my;
	Uint8 mstate = SDL_GetMouseState(&mx, &my);
	SetPlayerX(mx - player->width / 2.0f);

	if (mstate&SDL_BUTTON(1)) {
		if (paddlestick) {
			paddlestick = false;
			ball->SetDirection(1, -1);
		}
	}

	if (paddlestick) {
		StickBall();
	}

	CheckBoardCollisions();
	CheckPaddleCollisions();
	CheckBrickCollisions2();

	if (GetBrickCount() == 0) {
		NewGame();
	}

	level->Update(delta);
	player->Update(delta);

	if (!paddlestick) {
		ball->Update(delta);
	}
}

void Game::SetPlayerX(float x) {
	float newx;
	if (x < level->x) {
		// Upper bound
		newx = level->x;
	}
	else if (x + player->width > level->x + level->width) {
		// Lower bound
		newx = level->x + level->width - player->width;
	}
	else {
		newx = x;
	}
	player->x = newx;
}
// TODO:: Move to its own class
void Game::CheckBoardCollisions() {
	// Top and bottom collisions
	if (ball->y < level->y) {
		// Top
		// Keep the ball within the level and reflect the y-direction
		ball->y = level->y;
		ball->diry *= -1;
	}
	else if (ball->y + ball->height > level->y + level->height) {
		// Bottom

		// Ball lost
		ResetPlayer();
	}

	// Left and right collisions
	if (ball->x <= level->x) {
		// Left
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x;
		ball->dirx *= -1;
	}
	else if (ball->x + ball->width >= board->x + board->width) {
		// Right
		// Keep the ball within the level and reflect the x-direction
		ball->x = board->x + board->width - ball->width;
		ball->dirx *= -1;
	}
}

float Game::GetReflection(float hitx) {
	// Make sure the hitx variable is within the width of the player
	if (hitx < 0) {
		hitx = 0;
	}
	else if (hitx > player->width) {
		hitx = player->width;
	}

	// Everything to the left of the center of the paddle is reflected to the left
	// while everything right of the center is reflected to the right
	hitx -= player->width / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitx / (player->width / 2.0f));
}


void Game::CheckPaddleCollisions() {
	// Get the center x-coordinate of the ball
	float ballcenterx = ball->x + ball->width / 2.0f;

	// Check player collision
	if (ball->Collides(player)) {
		ball->y = player->y - ball->height;
		ball->SetDirection(GetReflection(ballcenterx - player->x), -1);
		//ball->SetDirection(0, -1);
	}
}

void Game::CheckBrickCollisions() {
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];

			// Check if brick is present
			if (brick.state) {
				// Brick x and y coordinates
				float brickx = level->brickoffsetx + level->x + i * LEVEL_BRWIDTH;
				float bricky = level->brickoffsety + level->y + j * LEVEL_BRHEIGHT;

				// Check ball-brick collision
				// Determine the collision using the half-widths of the rectangles
				float w = 0.5f * (ball->width + LEVEL_BRWIDTH);
				float h = 0.5f * (ball->height + LEVEL_BRHEIGHT);
				float dx = (ball->x + 0.5f*ball->width) - (brickx + 0.5f*LEVEL_BRWIDTH);
				float dy = (ball->y + 0.5f*ball->height) - (bricky + 0.5f*LEVEL_BRHEIGHT);

				if (fabs(dx) <= w && fabs(dy) <= h) {
					// Collision detected
					level->bricks[i][j].state = false;

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx) {
						if (wy > -hx) {
							// Bottom (y is flipped)
							BallBrickResponse(3);
						}
						else {
							// Left
							BallBrickResponse(0);
						}
					}
					else {
						if (wy > -hx) {
							// Right
							BallBrickResponse(2);
						}
						else {
							// Top (y is flipped)
							BallBrickResponse(1);
						}
					}
					return;
				}
			}
		}
	}
}

void Game::CheckBrickCollisions2() {
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];

			// Check if brick is present
			if (brick.state) {
				// Brick x and y coordinates
				float brickx = level->brickoffsetx + level->x + i * LEVEL_BRWIDTH;
				float bricky = level->brickoffsety + level->y + j * LEVEL_BRHEIGHT;

				// Center of the ball x and y coordinates
				float ballcenterx = ball->x + 0.5f*ball->width;
				float ballcentery = ball->y + 0.5f*ball->height;

				// Center of the brick x and y coordinates
				float brickcenterx = brickx + 0.5f*LEVEL_BRWIDTH;
				float brickcentery = bricky + 0.5f*LEVEL_BRHEIGHT;

				if (ball->x <= brickx + LEVEL_BRWIDTH && ball->x + ball->width >= brickx && ball->y <= bricky + LEVEL_BRHEIGHT && ball->y + ball->height >= bricky) {
					// Collision detected, remove the brick
					level->bricks[i][j].state = false;

					// Asume the ball goes slow enough to not skip through the bricks TODO:: Change with more powerups

					// Calculate ysize
					float ymin = 0;
					if (bricky > ball->y) {
						ymin = bricky;
					}
					else {
						ymin = ball->y;
					}

					float ymax = 0;
					if (bricky + LEVEL_BRHEIGHT < ball->y + ball->height) {
						ymax = bricky + LEVEL_BRHEIGHT;
					}
					else {
						ymax = ball->y + ball->height;
					}

					float ysize = ymax - ymin;

					// Calculate xsize
					float xmin = 0;
					if (brickx > ball->x) {
						xmin = brickx;
					}
					else {
						xmin = ball->x;
					}

					float xmax = 0;
					if (brickx + LEVEL_BRWIDTH < ball->x + ball->width) {
						xmax = brickx + LEVEL_BRWIDTH;
					}
					else {
						xmax = ball->x + ball->width;
					}

					float xsize = xmax - xmin;

					// The origin is at the top-left corner of the screen!
					// Set collision response
					if (xsize > ysize) {
						if (ballcentery > brickcentery) {
							// Bottom
							ball->y += ysize + 0.01f; // Move out of collision
							BallBrickResponse(3);
						}
						else {
							// Top
							ball->y -= ysize + 0.01f; // Move out of collision
							BallBrickResponse(1);
						}
					}
					else {
						if (ballcenterx < brickcenterx) {
							// Left
							ball->x -= xsize + 0.01f; // Move out of collision
							BallBrickResponse(0);
						}
						else {
							// Right
							ball->x += xsize + 0.01f; // Move out of collision
							BallBrickResponse(2);
						}
					}

					return;
				}
			}
		}
	}
}

void Game::BallBrickResponse(int dirindex) {
	// dirindex 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->dirx > 0) {
		// Ball is moving in the positive x direction
		if (ball->diry > 0) {
			// Ball is moving in the positive y direction
			// +1 +1
			if (dirindex == 0 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->diry < 0) {
			// Ball is moving in the negative y direction
			// +1 -1
			if (dirindex == 0 || dirindex == 1) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}
	else if (ball->dirx < 0) {
		// Ball is moving in the negative x direction
		if (ball->diry > 0) {
			// Ball is moving in the positive y direction
			// -1 +1
			if (dirindex == 2 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->diry < 0) {
			// Ball is moving in the negative y direction
			// -1 -1
			if (dirindex == 1 || dirindex == 2) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	ball->SetDirection(mulx*ball->dirx, muly*ball->diry);
}

int Game::GetBrickCount() {
	int brickcount = 0;
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		for (int j = 0; j < LEVEL_HEIGHT; j++) {
			Brick brick = level->bricks[i][j];
			if (brick.state) {
				brickcount++;
			}
		}
	}

	return brickcount;
}

void Game::Render(float delta) {
	SDL_RenderClear(renderer);

	level->Render(delta);
	player->Render(delta);
	ball->Render(delta);

	SDL_RenderPresent(renderer);
}