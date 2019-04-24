#include "GameObject.h"


GameObject::GameObject(std::string texture, SDL_Renderer* renderer) : m_renderer(renderer), x_pos(0), y_pos(0), width(1), height(1) {
	m_object_texture = TextureManager::load_texture(texture, m_renderer);
}

//GameObject::GameObject(SDL_Renderer* renderer) : m_renderer(renderer), x(0), y(0), width(1), height(1) {}

GameObject::~GameObject() {
	
}


bool GameObject::collision_with(GameObject* object) {
	if (x_pos + width > object->x_pos && x_pos < object->x_pos + object->width &&
		y_pos + height > object->y_pos && y_pos < object->y_pos + object->height) {
		return true;
	}
	else {
		return false;
	}
}