#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "constants.h"


class Object
{
	public:
		SDL_Rect rect;
		SDL_Color color;

		Object(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
		bool checkPlayerCollision(Object obj) const;
};