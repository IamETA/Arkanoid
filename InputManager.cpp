#include "InputManager.h"

namespace InputUtils {

	InputManager* InputUtils::InputManager::sInstance = NULL;

	InputManager* InputUtils::InputManager::Instance() {
		if (sInstance == NULL)
		{
			sInstance = new InputManager();
		}

		return sInstance;

	}

	void InputUtils::InputManager::Release() {
		delete sInstance;
		sInstance = NULL;
	}


	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}


}