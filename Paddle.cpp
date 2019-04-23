#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* renderer) : GameObject(renderer)
{
	SDL_Surface* surface = IMG_Load("paddle.png");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	width = 128;
	height = 32;

	y = 560;

}


Paddle::~Paddle()
{
	SDL_DestroyTexture(m_texture);
}

void Paddle::update(float delta) {}

void Paddle::render(float delta) {

	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;

	SDL_RenderCopy(renderer, m_texture, 0, &m_rect);

}
