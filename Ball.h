#ifndef BALL_H_
#define BALL_H_

#include "Item.h"

#include <math.h>

// Define a ball speed in pixels per second
// TODO:: A add increasing speed after each brick and/or powerups.
const float BALL_SPEED = 550;

class Ball : public Item {
public:
	Ball(SDL_Renderer* renderer);
	~Ball();

	void Update(float delta);
	void Render(float delta);

	void SetDirection(float dirx, float diry);

	float dirx, diry;

private:
	SDL_Texture* texture;

};

#endif