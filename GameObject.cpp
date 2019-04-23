#include "GameObject.h"


GameObject::GameObject(std::string texture, SDL_Renderer* renderer) : m_renderer(renderer), x(0), y(0), width(1), height(1) {
	m_object_texture = Game::TextureManager::load_texture(texture, renderer);
}

//GameObject::GameObject(SDL_Renderer* renderer) : renderer(renderer), x(0), y(0), width(1), height(1)  {}

GameObject::~GameObject() {

}

void GameObject::update(float delta) {
}

void GameObject::render(float delta) {
}

bool GameObject::collision_with(GameObject* object) {
	if (x + width > object->x && x < object->x + object->width &&
		y + height > object->y && y < object->y + object->height) {
		return true;
	}
	else {
		return false;
	}
}