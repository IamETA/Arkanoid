#include "Ball.h"



Ball::Ball(SDL_Renderer* renderer) : GameObject(renderer)
{
	SDL_Surface* surface = IMG_Load("transparentball.png");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	x = 0;
	y = 0;
	width = 24;
	height = 24;

}


Ball::~Ball()
{
	SDL_DestroyTexture(m_texture);
}

void Ball::update(float delta) {
	x += (m_dirx * delta);
	y += (m_diry * delta);
}

void Ball::render(float delta) {
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;

	SDL_RenderCopy(renderer, m_texture, 0, &m_rect);
}

void Ball::set_direction(float diry, float dirx) {

	float length = sqrt((dirx * dirx) + (diry * diry));
	this->m_dirx = EASY_BALL_SPEED * (dirx / length);
	this->m_diry = EASY_BALL_SPEED * (diry / length);


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
