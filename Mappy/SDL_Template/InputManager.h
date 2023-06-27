#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <SDL.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#endif
#include <string>
#include "MathHelper.h"

namespace SDLFramework {

	class InputManager
	{
	public:
		enum MouseButton { Left = 0, Right, Middle, Back, Forward };

	private:
		static InputManager * sInstance;
		const Uint8 * mKeyboardState;
		Uint8 * mPrevKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

	public:

		static InputManager * Instance();
		static void Release();

		bool KeyDown(SDL_Scancode scancode);
		bool KeyPressed(SDL_Scancode scancode);
		bool KeyReleased(SDL_Scancode scancode);

		bool MouseButtonDown(MouseButton mouseButton);
		bool MouseButtonPressed(MouseButton mouseButton);
		bool MouseButtonReleased(MouseButton mouseButton);

		Vector2 MousePosition();

		void Update();
		void UpdatePrevInput();

	private:
		InputManager();
		~InputManager();
	};
}
#endif