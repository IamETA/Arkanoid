#pragma once
#include "GameObject.h"


//Variabler for å endre hastigheten til ballen -

const float EASY_BALL_SPEED = 500;
const float MEDIUM_BALL_SPEED = 650;
const float HARD_BALL_SPEED = 750;

class Ball : public GameObject
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();
	SDL_Color* color;

	float ball_difficulty{ 0 };
	void update(float delta);
	void render();
	void set_direction(float diry, float dirx);
	void change_ball_color(SDL_Color* new_color);
	float m_dirY{ 0 }, m_dirX{ 0 };
	bool released{ false };
	

private: 

	SDL_Rect m_rect{ 0 };
	//Variabler for å endre hastigheten til ballen -

	const float EASY_BALL_SPEED = 550;
	const float MEDIUM_BALL_SPEED = 650;
	const float HARD_BALL_SPEED = 750;

};

