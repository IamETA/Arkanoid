#pragma once
#include "GameObject.h"

const float EASY_BALL_SPEED = 550;
const float MEDIUM_BALL_SPEED = 650;
const float HARD_BALL_SPEED = 750;

class Ball : public GameObject
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();
	SDL_Color* color;

	float ball_difficulty{ 1 };
	void update(float delta);
	void render();
	void set_direction(float diry, float dirx);
	void change_ball_color(SDL_Color* new_color);
	float m_dir_y{ 0 }, m_dir_x{ 0 };
	bool released{ false };
	

private: 
	SDL_Rect m_rect{ 0 };
};

