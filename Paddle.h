#pragma once
#include "GameObject.h"
#include "InputManager.h"

class Paddle :
	public GameObject
{
public:
	Paddle(SDL_Renderer* renderer);
	~Paddle();
	void update(float delta) override;
	void render() override;
private: 
	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_rect{ 0 };

};

