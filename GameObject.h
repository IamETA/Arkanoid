#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"

/* Parent class to all the game objects 
*/

class GameObject
{
public:

	//Constructors

	//Default inline
	explicit GameObject() {};
	explicit GameObject(std::string texture, SDL_Renderer* renderer);


	//GameObject(SDL_Renderer* renderer);

	virtual ~GameObject();

	float x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 };

	virtual void update(float delta) {}
	virtual void render() {}

	bool collision_with(GameObject *object);
protected:
	SDL_Renderer* m_renderer{ nullptr };
	SDL_Texture* m_object_texture{ nullptr };

	
};

