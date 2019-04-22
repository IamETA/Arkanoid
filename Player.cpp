#include "Player.h"

Player::Player(SDL_Renderer* renderer) : Item(renderer) {
	SDL_Surface* surface = IMG_Load("Player.png"); // Bytte til paddle.bmp
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	width = 128;
	height = 32;

	y = 560;
}

Player::~Player() {
	// Clean resources
	SDL_DestroyTexture(texture);
}


void Player::Update(float delta) {

}

void Player::Render(float delta) {
	SDL_Rect rect;
	rect.x = (int)(x + 0.5f);
	rect.y = (int)(y + 0.5f);
	rect.w = width;
	rect.h = height;
	SDL_RenderCopy(renderer, texture, 0, &rect);
}