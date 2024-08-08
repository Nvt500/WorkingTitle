#pragma once
#include <SDL.h>


class KeyboardHandler
{
	public:
		bool keyPressed(SDL_Scancode keycode) const;
		bool keyPressed();

	private:
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);
};