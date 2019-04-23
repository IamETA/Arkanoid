#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:
	Ball(std::string texture, SDL_Renderer* renderer);
	~Ball();

	void update(float delta);
	void render();
	void set_direction(float diry, float dirx);

	void change_ball_color();
	
	float m_dirY{ 0 }, m_dirX{ 0 };

private: 
	SDL_Rect m_rect{ 0 };
	//Variabler for å endre hastigheten til ballen -

	const float EASY_BALL_SPEED = 550;
	const float MEDIUM_BALL_SPEED = 650;
	const float HARD_BALL_SPEED = 750;


};

