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

	bool InputManager::KeyDown(SDL_Scancode scanCode) 
	{
		return mKeyBoardStates[scanCode];
	}

	void InputManager::Update() 
	{
		mKeyBoardStates = SDL_GetKeyboardState(NULL);
		mouseState = SDL_GetMouseState(&mx, &my);
	}


}