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
	SDL_DestroyTexture(m_object_texture);
}

void Ball::update(float delta) {
	x += (m_dirX * delta) * ball_difficulty;
	y -= (m_dirY * delta) * ball_difficulty;
}

void Ball::render() {
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;
	SDL_SetRenderDrawColor(m_renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(m_renderer, &m_rect);
	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0,0);

}

void Ball::set_direction(float diry, float dirx) {
	//this->m_dirY = diry;
	float length = sqrt((dirx * dirx) + (diry * diry));
	this->m_dirX = EASY_BALL_SPEED * (dirx / length);
	this->m_dirY = EASY_BALL_SPEED * (diry / length);
	//this->m_dirX = dirx;
}

// Change color of ball
// Example: ball->change_ball_color(new SDL_Color{ (Uint8)(rand() % 255),(Uint8)(rand() % 255),(Uint8)(rand() % 255), 1 });
void Ball::change_ball_color(SDL_Color* new_color) {
	delete color;
	color = new_color;
}

