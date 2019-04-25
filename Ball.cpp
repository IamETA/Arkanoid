#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer) : GameObject(".\\textures\\ball.png", renderer)
{
	x = 32;
	y = 32;
	width = 32;
	height = 32;
	color = new SDL_Color{ 0,199,0,1 };
	set_direction(EASY_BALL_SPEED, 100);
}

Ball::~Ball()
{
	delete color;
	SDL_DestroyTexture(m_object_texture);
}

void Ball::update(float delta) 
{
	x += (m_dir_x * delta) * ball_difficulty;
	y -= (m_dir_y * delta) * ball_difficulty;
}

void Ball::render() 
{
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;

	SDL_SetRenderDrawColor(m_renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(m_renderer, &m_rect);
	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0,0);

}

void Ball::set_direction(float diry, float dirx) 
{
	// Normalize direction speed
	float length = sqrt((dirx * dirx) + (diry * diry));
	this->m_dir_x = EASY_BALL_SPEED * (dirx / length);
	this->m_dir_y = EASY_BALL_SPEED * (diry / length);
}

void Ball::change_ball_color(SDL_Color* new_color) 
{
	delete color;
	color = new_color;
}

