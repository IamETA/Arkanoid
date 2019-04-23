#include "Ball.h"

Ball::Ball(std::string texture, SDL_Renderer* renderer) : GameObject(texture, m_renderer)
{
	m_object_texture = TextureManager::load_texture(texture, renderer);
	
	x = 50;
	y = 50;
	width = 24;
	height = 24;
}

Ball::~Ball()
{
	SDL_DestroyTexture(m_object_texture);
}

void Ball::update(float delta) {
	x += (m_dirX * delta);
	y += (m_dirY * delta);
}

void Ball::render() {
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;

	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);
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
