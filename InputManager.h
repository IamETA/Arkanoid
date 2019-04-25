#pragma once

#include "SDL.h"

namespace InputUtils {

	class InputManager
	{
	private:
		static InputManager* sInstance;
		const Uint8* m_keyboard_states{ NULL };
		Uint32 mouse_state{ NULL };
		int m_x{ 0 }, m_y{ 0 };

	public:
		static InputManager* Instance();
		void update();
		static void Release();
		bool key_down(SDL_Scancode scanCode);
		int getX() { return m_x; }

		explicit InputManager();
		~InputManager();

	};

}

