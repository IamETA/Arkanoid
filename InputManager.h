#pragma once

#include "SDL.h"

namespace InputUtils {

	class InputManager
	{
	private:
		static InputManager* sInstance;
		const Uint8* mKeyBoardStates{ NULL };
		Uint32 mouseState{ NULL };
		int mx{ 0 }, my{ 0 };

	public:
		static InputManager* Instance();
		void Update();
		static void Release();
		bool KeyDown(SDL_Scancode scanCode);
		int getX() { return mx; }

		explicit InputManager();
		~InputManager();

	};

}

