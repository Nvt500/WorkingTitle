#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "constants.h"


class Text
{
	public:
		TTF_Font* font = nullptr;
		SDL_Color color;
		std::string text;
		SDL_Texture *texture = nullptr;
		SDL_Rect rect;

		Text();
		Text(std::string fontFilePath, int fontSize, Uint8 r, Uint8 g, Uint8 b, std::string text, int x, int y, SDL_Renderer* renderer);
		void updateText(std::string text, SDL_Renderer* renderer);
		void updateColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer);
		void center();
		void destroy();
};