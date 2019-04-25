#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer) : GameObject(".\\textures\\ball.png", renderer)
{
	x = 32;
	y = 32;
	width = 32;
	height = 32;
	set_direction(EASY_BALL_SPEED, 300);
}

Ball::~Ball()
{
	SDL_DestroyTexture(m_object_texture);
}

void Ball::update(float delta) {
	x += (m_dirX * delta);
	y -= (m_dirY * delta);
}

void Ball::render() {
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 1);
	SDL_RenderFillRect(m_renderer, &m_rect);
	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0,0);

}

void Ball::set_direction(float diry, float dirx) {
	//this->m_dirX = dirx;
	//this->m_dirY = diry;
	float length = sqrt((dirx * dirx) + (diry * diry));
	this->m_dirX = EASY_BALL_SPEED * (dirx / length);
	this->m_dirY = EASY_BALL_SPEED * (diry / length);
}

void Ball::change_ball_color(SDL_Color* new_color) {

}

/* EXTRA FEATURE SOM BRUKES TIL Å HOLDE SCORE - "Poeng er hver hit"
void Ball::incrementHitCount()
{
  m_HitCount++;
  if (mHitCount == 4 || mHitCount == 12) {
	incrementVelocity();
  }
}

void Ball::incrementVelocity()
{
  mVelocity += mVelocityIncrementStep;
}
*/
