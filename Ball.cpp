#include "Ball.h"

Ball::Ball(std::string texture, SDL_Renderer* renderer) : GameObject(".\\textures\\transparentball.png", renderer)
{
	x_pos = 32;
	y_pos = 32;
	width = 32;
	height = 32;
	set_direction(1, 1);
}

Ball::~Ball()
{
	SDL_DestroyTexture(m_object_texture);
}

void Ball::update(float delta) {
	x_pos += (m_dirX * delta);
	y_pos += (m_dirY * delta);
}

void Ball::render() {
	m_rect.x = (int)(x_pos + 0.5f);
	m_rect.y = (int)(y_pos + 0.5f);
	m_rect.w = width;
	m_rect.h = height;
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 1);
	SDL_RenderFillRect(m_renderer, &m_rect);
	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0,0);

}

void Ball::set_direction(float diry, float dirx) {

	float length = sqrt((dirx * dirx) + (diry * diry));
	this->m_dirX = EASY_BALL_SPEED * (dirx / length);
	this->m_dirY = EASY_BALL_SPEED * (diry / length);


}

void Ball::change_ball_color() {

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
