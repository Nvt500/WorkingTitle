#include "KeyboardHandler.h"


bool KeyboardHandler::keyPressed(SDL_Scancode keycode) const
{
	return this->keyboard[keycode] != 0;
}


bool KeyboardHandler::keyPressed()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		if (this->keyboard[i] != 0)
			return true;
	}
	return false;
}