#include "Ball.h"



Ball::Ball(SDL_Renderer* renderer) : GameObject(renderer)
{
	SDL_Surface* surface = IMG_Load("ball.png");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	width = 24;
	height = 24;
}


Ball::~Ball()
{
}

void Ball::change_ball_color() {

}
