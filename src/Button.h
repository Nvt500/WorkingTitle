#pragma once
#include <SDL.h>
#include "Text.h"


class Button
{
	public:
		Text text;
		SDL_Rect background;
		SDL_Color backgroundColor;

		Button(std::string fontFilePath, int fontSize, Uint8 r, Uint8 g, Uint8 b, std::string text, int x, int y, SDL_Renderer* renderer, bool center);
		void updateBackground(int w, int h, Uint8 r, Uint8 g, Uint8 b);
		void updateBackgroundSize(int w, int h);
		void updateBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
		void updateText(std::string text, SDL_Renderer* renderer, bool center);
		void updateTextColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer);
		void destroy();
		bool isClicked(SDL_Event event) const;
		bool isHovered(SDL_Event event) const;
		void changeColorWhenHover(SDL_Event event, Uint8 r1, Uint8 g1, Uint8 b1, Uint8 r2, Uint8 g2, Uint8 b2, SDL_Renderer* renderer);
};