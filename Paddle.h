#pragma once
#include "GameObject.h"
class Paddle :
	public GameObject
{
public:
	Paddle(SDL_Renderer* renderer);
	~Paddle();

	void update(float delta);
	void render();

private: 

	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_rect;

};

