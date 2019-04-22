#ifndef PLAYER_H_
#define PLAYER_H_

#include "Item.h"

class Player : public Item {
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void Update(float delta);
	void Render(float delta);

private:
	SDL_Texture* texture;
};

#endif