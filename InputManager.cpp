#include "InputManager.h"

namespace InputUtils {

	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::Instance() 
	{
		if (sInstance == nullptr)
		{
			sInstance = new InputManager();
		}

		return sInstance;

	}

	void InputManager::Release() 
	{
		delete sInstance;
		sInstance = nullptr;
	}


	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	bool InputManager::key_down(SDL_Scancode scanCode) 
	{
		return m_keyboard_states[scanCode];
	}

	void InputManager::update() 
	{
		m_keyboard_states = SDL_GetKeyboardState(NULL);
		mouse_state = SDL_GetMouseState(&m_x, &m_y);
	}


}