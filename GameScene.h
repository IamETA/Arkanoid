#pragma once

#include <iostream>
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <SDL.h>
#include "TextureManager.h"
#include "Ball.h"
#include "Level.h"
#include "Paddle.h"
#include "Highscores.h"

enum brick_hit_face { top, bottom, left, right };

class GameScene final : public Scene
{
private:
	const int stats_left_margin{ 30 };
	const int stats_height_margin{ 40 };


	int life_left{ 3 };
	int current_level{ 1 };
	int score{ 0 };
	int difficulty{ 1 };

	bool move_left{ false };
	bool move_right{ false };

	Paddle* paddle{ nullptr };
	Ball* ball{ nullptr };
	Level* level{ nullptr };
	Highscores* highscore{ nullptr };
	InputUtils::InputManager*  input{ nullptr };

	SDL_Texture* m_life_text{ nullptr };
	SDL_Texture* m_score_text{ nullptr };
	SDL_Texture* m_difficulty_text{ nullptr };
	SDL_Texture* m_level_text{ nullptr };
	SDL_Texture* m_logo{ nullptr };

	SDL_Rect m_life_text_pos{ 0,0,0,0 };
	SDL_Rect m_score_text_pos{ 0,0,0,0 };
	SDL_Rect m_difficulty_text_pos{ 0,0,0,0 };
	SDL_Rect m_level_text_pos{ 0,0,0,0 };
	SDL_Rect m_logo_pos{ 0,0,0,0 };

	void update_stats_lives();
	void update_stats_score();
	void update_stats_difficulty();
	void update_stats_level();
	void update_logo();


	void update_paddle_position();
	void update_ball_check_released();
	void update_map_collision_detection();
	void update_paddle_collision_detection();
	void update_level_collision_detection();
	int get_brick_num();
	void level_up();

	//The sound effects that will be used
	Mix_Chunk *cPaddle{ NULL };
	Mix_Chunk *cBrick{ NULL };
	Mix_Chunk *cBottom{ NULL };
	Mix_Chunk *cSides{ NULL };
	Mix_Chunk *cNextRound{ NULL };
	Mix_Chunk *cGameOver{ NULL };

public:
	GameScene(Game& game);
	~GameScene();

	void update(float delta) override;
	void render() override;
	void enter() override;
	void exit() override;
	void key_up(SDL_KeyboardEvent & event) override;
	void key_down(SDL_KeyboardEvent & event) override;
	void mouse_down(SDL_KeyboardEvent & event) override;

	float get_reflection(float hitx); 
	void brick_hit(brick_hit_face face);
	void reset_ball();

};

