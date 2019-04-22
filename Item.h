#ifndef ITEM_H_
#define ITEM_H_

#include "SDL.h"
#include "SDL_image.h"

class Item {
public:
	Item(SDL_Renderer* renderer);
	virtual ~Item();

	float x, y, width, height;

	virtual void Update(float delta);
	virtual void Render(float delta);

	bool Collides(Item* other);
protected:
	SDL_Renderer* renderer;

};

#endif