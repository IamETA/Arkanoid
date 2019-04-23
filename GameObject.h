#pragma once

#include "SDL.h"
#include "SDL_image.h"

/* Parent class to all the game objects
*/

class GameObject
{
public:

	explicit GameObject(SDL_Renderer* renderer);
	virtual ~GameObject();

	float x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 };

	virtual void update(float delta);
	virtual void render(float delta);

	bool collision_with(GameObject *object);
protected:
	SDL_Renderer* renderer{ nullptr };


};

