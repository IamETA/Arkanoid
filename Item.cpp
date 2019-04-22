#include "Item.h"

Item::Item(SDL_Renderer* renderer) {
	this->renderer = renderer;

	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

Item::~Item() {
}

void Item::Update(float delta) {
}

void Item::Render(float delta) {
}

bool Item::Collides(Item* other) {
	if (x + width > other->x && x < other->x + other->width &&
		y + height > other->y && y < other->y + other->height) {
		return true;
	}
	return false;
}