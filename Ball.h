#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();

	void update(float delta);
	void render(float delta);
	void set_direction(float diry, float dirx);

	void change_ball_color();
	
	float m_diry{ 0 }, m_dirx{ 0 };

private: 
	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_rect;


	//Variabler for å endre hastigheten til ballen -

	const float EASY_BALL_SPEED = 550;
	const float MEDIUM_BALL_SPEED = 650;
	const float HARD_BALL_SPEED = 750;


};

