#include "Paddle.h"
#include "InputManager.h"

Paddle::Paddle(SDL_Renderer* renderer) : GameObject(".\\textures\\paddle.png",renderer)
{	
	width = 128;
	height = 68;
}


Paddle::~Paddle()
{
	SDL_DestroyTexture(m_texture);
}

void Paddle::update(float delta) {
	m_rect.x = (int)(x + 0.5f);
	m_rect.y = (int)(y + 0.5f);
	m_rect.w = width;
	m_rect.h = height;
}

void Paddle::render() {

	SDL_RenderCopy(m_renderer, m_object_texture, 0, &m_rect);

}
