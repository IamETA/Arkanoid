#include "GameScene.h"
#include "MenuScene.h"
#include "HighscoreScene.h"
#include <iostream>


GameScene::GameScene(Game& game) : Scene(game)
{
	std::cout << "Initializing GameScene..." << std::endl;

	input = InputUtils::InputManager::Instance();
	SDL_Renderer* renderer = game.get_renderer();

	//Load the sound effects
	cPaddle = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (1).wav");
	cBrick = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (2).wav");
	cBottom = Mix_LoadWAV(".\\sounds\\doh.wav");
	cSides = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (3).wav");
	cNextRound = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (9).wav");
	cGameOver = Mix_LoadWAV(".\\sounds\\Arkanoid SFX (11).wav");

	//Game objects
	paddle = new Paddle(renderer);
	ball = new Ball(renderer);
	level = new Level(renderer);
	highscore = new Highscores();

	//set paddle height to correct height
	paddle->y = level->height - paddle->height;

	//Create the start level
	level->next_level(current_level);
}
GameScene::~GameScene()
{
	delete paddle;
	delete ball;
	delete level;
	delete highscore;
	//Free sound effects
	Mix_FreeChunk(cBrick);
	Mix_FreeChunk(cBottom);
	Mix_FreeChunk(cPaddle);
	Mix_FreeChunk(cNextRound);
	Mix_FreeChunk(cSides);
	Mix_FreeChunk(cGameOver);


	#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

	// release all reserved textures.
	RELEASE_TEXTURE(m_score_text);
	RELEASE_TEXTURE(m_life_text);
	RELEASE_TEXTURE(m_difficulty_text);
	RELEASE_TEXTURE(m_logo);
	RELEASE_TEXTURE(m_level_text);

	std::cout << "GameScene destroyed" << std::endl;
	
}
void GameScene::update(float delta)
{
	paddle->update(delta);
	ball->update(delta);
	level->update(delta);

	update_paddle_position();
	update_ball_check_released();

	//Collision detection
	update_paddle_collision_detection();
	update_level_collision_detection();
	update_map_collision_detection();
}
void GameScene::reset_ball() 
{
	//Remove 1 life
	life_left--;
	ball->released = false;
	update_stats_lives();
	ball->set_direction(EASY_BALL_SPEED, 100);
}
void GameScene::level_up() 
{

	int brick_count = get_brick_num();
	if (brick_count == 0) 
	{
		// Rest the ball to paddle with next level
		Mix_PlayChannel(-1, cNextRound, 0);
		ball->released = false;
		ball->set_direction(EASY_BALL_SPEED, 100);
		level->next_level(current_level);
		if (current_level == 3)
		{
			current_level = 0; // reset to loop the levels
			difficulty++;
			update_stats_difficulty();
			ball->ball_difficulty = 1 + (difficulty / 20);
		}

		if (difficulty == 2) {
			ball->change_ball_color(new SDL_Color{ 0,0,255,1 });
		}
		else if (difficulty == 3) {
			ball->change_ball_color(new SDL_Color{ 255,0,0,1 });
		}
		current_level++;
		level->next_level(current_level);
		
		update_stats_level();
	}
}
void GameScene::update_level_collision_detection() 
{
	for (int i = 0; i < LEVEL_WIDTH; i++) 
	{
		for (int j = 0; j < LEVEL_HEIGHT; j++) 
		{
			Brick brick = level->bricks[i][j];

			// Check if brick is present
			if (brick.state) {
				// Brick x and y coordinates
				float brickx = level->brick_offset_x + level->x + i * LEVEL_BRWIDTH;
				float bricky = level->brick_offset_y + level->y + j * LEVEL_BRHEIGHT;

				// Center of the ball x and y coordinates
				float ballcenterx = ball->x + 0.5f*ball->width;
				float ballcentery = ball->y + 0.5f*ball->height;

				// Center of the brick x and y coordinates
				float brickcenterx = brickx + 0.5f*LEVEL_BRWIDTH;
				float brickcentery = bricky + 0.5f*LEVEL_BRHEIGHT;

				if (ball->x <= brickx + LEVEL_BRWIDTH && ball->x + ball->width >= brickx && ball->y <= bricky + LEVEL_BRHEIGHT && ball->y + ball->height >= bricky) 
				{
					// Collision detected, remove the brick
					Mix_PlayChannel(-1, cBrick, 0);
					if (brick.hp == 0) 
					{
						level->bricks[i][j].state = false;
					}
					else 
					{
						level->bricks[i][j].hp -= 1;
						// Change color of bricks depending on hit points
						if (current_level == 1) 
						{
							if (brick.type == 3) 
							{
								level->bricks[i][j].type = 2;
							}
							if (brick.type == 2) 
							{
								level->bricks[i][j].type = 1;
							}
							if (brick.type == 1) 
							{
								level->bricks[i][j].type = 0;
							}
						}
						if (current_level == 2) 
						{
							if (brick.type == 1) 
							{
								level->bricks[i][j].type = 3;
							}
						}
					}
					// Adds score on hit, not on removel of bricks
					if (brick.hp >= 0) 
					{
						score++;
						update_stats_score();
					}

					// Calculate ysize
					float ymin = 0;
					if (bricky > ball->y) 
					{
						ymin = bricky;
					}
					else 
					{
						ymin = ball->y;
					}

					float ymax = 0;
					if (bricky + LEVEL_BRHEIGHT < ball->y + ball->height)
					{
						ymax = bricky + LEVEL_BRHEIGHT;
					}
					else
					{
						ymax = ball->y + ball->height;
					}

					float ysize = ymax - ymin;

					// Calculate xsize
					float xmin = 0;
					if (brickx > ball->x) 
					{
						xmin = brickx;
					}
					else {
						xmin = ball->x;
					}

					float xmax = 0;
					if (brickx + LEVEL_BRWIDTH < ball->x + ball->width) 
					{
						xmax = brickx + LEVEL_BRWIDTH;
					}
					else
					{
						xmax = ball->x + ball->width;
					}

					float xsize = xmax - xmin;

					// The origin is at the top-left corner of the screen!
					// Set collision response
					if (xsize > ysize) 
					{
						if (ballcentery > brickcentery) 
						{
							// Bottom
							ball->y += ysize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::bottom);
						}
						else 
						{
							// Top
							ball->y -= ysize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::top);
						}
					}
					else 
					{
						if (ballcenterx < brickcenterx) 
						{
							// Left
							ball->x -= xsize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::left);
						}
						else
						{
							// Right
							ball->x += xsize + 0.01f; // Move out of collision
							brick_hit(brick_hit_face::right);
						}
					}

					return;
				}
			}
		}
	}
}
void GameScene::brick_hit(brick_hit_face face) 
{
	// dirindex 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->m_dir_x > 0) 
	{
		// Ball is moving in the positive x direction
		if (ball->m_dir_y > 0) 
		{
			// Ball is moving in the positive y direction
			// +1 +1
			if (face == brick_hit_face::left || face == brick_hit_face::right)
			{
				mulx = -1;
			}
			else 
			{
				muly = -1;
			}
		}
		else if (ball->m_dir_y < 0) 
		{
			// Ball is moving in the negative y direction
			// +1 -1
			if (face == brick_hit_face::left || face == brick_hit_face::right)
			{
				mulx = -1;
			}
			else
			{
				muly = -1;
			}
		}
	}
	else if (ball->m_dir_x < 0) 
	{
		// Ball is moving in the negative x direction
		if (ball->m_dir_y > 0)
		{
			// Ball is moving in the positive y direction
			// -1 +1
			//
			if (face == brick_hit_face::left || face == brick_hit_face::right)
			{
				mulx = -1;
			}
			else 
			{
				muly = -1;
			}
		}
		else if (ball->m_dir_y < 0) 
		{
			// Ball is moving in the negative y direction
			// -1 -1
			if (face == brick_hit_face::left || face == brick_hit_face::right)
			{
				mulx = -1;
			}
			else 
			{
				muly = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	ball->set_direction(muly*ball->m_dir_y, mulx*ball->m_dir_x);
	level_up();
}

// Contains gameover logic when ball hits bottom
void GameScene::update_map_collision_detection()
{
	// Top and bottom collisions
	if (ball->y < level->y) 
	{
		// Top
		// Keep the ball within the level and reflect the y-direction
		ball->y = level->y;
		ball->m_dir_y *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
	else if (ball->y + ball->height > level->y + level->height) 
	{
		// Bottom

		// Ball lost
		reset_ball();
		if (life_left == 0) 
		{
			Mix_PlayChannel(-1, cGameOver, 0);
			highscore->read_file();
			highscore->write_file(score);

			mGame.enter_scene(std::make_shared<HighscoreScene>(mGame));
			return;

		}
		else
		{
			Mix_PlayChannel(-1, cBottom, 0);
		}

	}

	// Left and right collisions
	if (ball->x <= level->x + level->brick_offset_x) 
	{
		// Left
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x + level->brick_offset_x;
		ball->m_dir_x *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
	else if (ball->x + ball->width >= level->x + level->width) 
	{
		// Right
		// Keep the ball within the level and reflect the x-direction
		ball->x = level->x + level->width - ball->width;
		ball->m_dir_x *= -1;
		Mix_PlayChannel(-1, cSides, 0);
	}
}
float GameScene::get_reflection(float hitx)
{
	// Make sure the hitx variable is within the width of the player
	if (hitx < 0)
	{
		hitx = 0;
	}
	else if (hitx > paddle->width) 
	{
		hitx = paddle->width;
	}

	// Everything to the left of the center of the paddle is reflected to the left
	// while everything right of the center is reflected to the right
	hitx -= paddle->width / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitx / (paddle->width / 2.0f));
}
void GameScene::update_paddle_collision_detection() 
{
	// Get the center x-coordinate of the ball
	float ballcenterx = ball->x + ball->width / 2.0f;

	// Check player collision
	if (ball->collision_with(paddle)) 
	{
		ball->y = paddle->y - ball->height;
		ball->set_direction(EASY_BALL_SPEED,EASY_BALL_SPEED * get_reflection(ballcenterx - paddle->x));
		Mix_PlayChannel(-1, cPaddle, 0);
	}
}
void GameScene::update_paddle_position()
{
	static int oldx;
	if (oldx != input->getX()) 
	{
		paddle->x = input->getX() - paddle->width / 2.0f;
		oldx = input->getX();
	}
	if (move_left) 
	{
		paddle->x -= 0.5;
	}
	if (move_right)
	{
		paddle->x+=0.5;
	}

	if (paddle->x < level->brick_offset_x) { paddle->x = level->brick_offset_x; }
	if (paddle->x > (level->width - paddle->width)) {
		paddle->x = (level->width - paddle->width);
	}
}
void GameScene::update_ball_check_released()
{
	if (!ball->released)
	{
		ball->x = paddle->x + paddle->width / 2 - ball->width / 2;
		ball->y = paddle->y - ball->height;
	}
}
void GameScene::render()
{
	paddle->render();
	ball->render();
	level->render();

	//render stats
	SDL_Renderer* renderer = mGame.get_renderer();
	SDL_RenderCopy(renderer, m_life_text, nullptr, &m_life_text_pos);
	SDL_RenderCopy(renderer, m_score_text, nullptr, &m_score_text_pos);
	SDL_RenderCopy(renderer, m_difficulty_text, nullptr, &m_difficulty_text_pos);
	SDL_RenderCopy(renderer, m_level_text, nullptr, &m_level_text_pos);
	SDL_RenderCopy(renderer, m_logo, nullptr, &m_logo_pos);
	//SDL_RenderCopy(renderer, mLogo, nullptr, &mLivesTextPosition);
}
int GameScene::get_brick_num() 
{
	int bricknum = 0;
	for (int i = 0; i < LEVEL_WIDTH; i++)
	{
		for (int j = 0; j < LEVEL_HEIGHT; j++)
		{
			Brick brick = level->bricks[i][j];
			if (brick.state && brick.hp >= 0) 
			{ // Does not count industribable bricks
				bricknum++;
			}
		}
	}
	return bricknum;
}
//Create/draw/update status
void GameScene::update_stats_lives()
{
	if (m_life_text) SDL_DestroyTexture(m_life_text);

	TTF_Font* font = mGame.get_font();
	SDL_Renderer* renderer = mGame.get_renderer();

	auto sLivesText = "Lives: " + std::to_string(life_left);
	m_life_text = TextureManager::create_text(sLivesText, renderer, font);
	SDL_QueryTexture(m_life_text, nullptr, nullptr, &m_life_text_pos.w, &m_life_text_pos.h);
	m_life_text_pos.y = stats_height_margin * 4;
	m_life_text_pos.x = level->width + stats_left_margin;
}
void GameScene::update_stats_score() 
{

	if (m_score_text) SDL_DestroyTexture(m_score_text);

	TTF_Font* font = mGame.get_font();
	SDL_Renderer* renderer = mGame.get_renderer();

	auto sScoreText = "Score: " + std::to_string(score);
	m_score_text = TextureManager::create_text(sScoreText, renderer, font);
	SDL_QueryTexture(m_score_text, nullptr, nullptr, &m_score_text_pos.w, &m_score_text_pos.h);
	m_score_text_pos.y = stats_height_margin * 5;
	m_score_text_pos.x = level->width + stats_left_margin;
}
void GameScene::update_stats_difficulty() 
{

	if (m_difficulty_text) SDL_DestroyTexture(m_difficulty_text);

	TTF_Font* font = mGame.get_font();
	SDL_Renderer* renderer = mGame.get_renderer();

	auto sDifficultyText = "Difficulty: " + std::to_string(difficulty);
	m_difficulty_text = TextureManager::create_text(sDifficultyText, renderer, font);
	SDL_QueryTexture(m_difficulty_text, nullptr, nullptr, &m_difficulty_text_pos.w, &m_difficulty_text_pos.h);
	m_difficulty_text_pos.y = stats_height_margin * 6;
	m_difficulty_text_pos.x = level->width + stats_left_margin;

}
void GameScene::update_stats_level()
{

	if (m_level_text) SDL_DestroyTexture(m_level_text);

	TTF_Font* font = mGame.get_font();
	SDL_Renderer* renderer = mGame.get_renderer();

	auto sLevelText = "Level: " + std::to_string(current_level);
	m_level_text = TextureManager::create_text(sLevelText, renderer, font);
	SDL_QueryTexture(m_level_text, nullptr, nullptr, &m_level_text_pos.w, &m_level_text_pos.h);
	m_level_text_pos.y = stats_height_margin * 7;
	m_level_text_pos.x = level->width + stats_left_margin;

}
void GameScene::update_logo() 
{

	if (m_logo) SDL_DestroyTexture(m_logo);

	SDL_Renderer* renderer = mGame.get_renderer();

	m_logo = m_logo = TextureManager::load_texture(".\\textures\\logo.png", renderer);
	m_logo_pos.h = 100;
	m_logo_pos.w = 200;
	m_logo_pos.x = level->width + stats_left_margin;
	m_logo_pos.y = 30;
}

//Events
void GameScene::enter()
{
	update_stats_difficulty();
	update_stats_level();
	update_stats_lives();
	update_stats_score();
	update_logo();
}
void GameScene::exit()
{

}
void GameScene::key_up(SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym) 
	{
	case SDLK_LEFT:
		move_left = false;
		break;
	case SDLK_RIGHT:
		move_right = false;
		break;
	}
}
void GameScene::key_down(SDL_KeyboardEvent & event)
{
	switch (event.keysym.sym) 
	{
	case SDLK_ESCAPE:
		mGame.enter_scene(std::make_shared<MenuScene>(mGame));
		break;
	case SDLK_LEFT: 
		move_left = true;
		break;
	case SDLK_RIGHT:
		move_right = true;
		break;
	}
}
void GameScene::mouse_down(SDL_KeyboardEvent & event)
{
	/*
	switch (event.keysym.sym) {
	case SDLK_|:
		mGame.enterScene(std::make_shared<MenuScene>(mGame));
		break;
	}*/
	ball->released = true;
}
