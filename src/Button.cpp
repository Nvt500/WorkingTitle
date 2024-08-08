#include "Button.h"


Button::Button(std::string fontFilePath, int fontSize, Uint8 r, Uint8 g, Uint8 b, std::string text, int x, int y, SDL_Renderer* renderer, bool center)
{
	this->text = Text(fontFilePath, fontSize, r, g, b, text, x, y, renderer);
	if (center)
		this->text.center();
	this->background = this->text.rect;
	this->backgroundColor = {0, 0, 0, 255};
}


void Button::updateBackground(int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
	this->background.x -= (w - this->background.w) / 2;
	this->background.y -= (h - this->background.h) / 2;
	this->background.w = w;
	this->background.h = h;

	this->backgroundColor.r = r;
	this->backgroundColor.g = g;
	this->backgroundColor.b = b;
}


void Button::updateBackgroundSize(int w, int h)
{
	
	this->background.x -= (w - this->background.w) / 2;
	this->background.y -= (h - this->background.h) / 2;
	this->background.w = w;
	this->background.h = h;
}


void Button::updateBackgroundColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->backgroundColor.r = r;
	this->backgroundColor.g = g;
	this->backgroundColor.b = b;
}


void Button::updateText(std::string text, SDL_Renderer* renderer, bool center)
{
	this->text.updateText(text, renderer);
	if (center)
		this->text.center();
	
	this->background.x = this->text.rect.x;
	this->background.y = this->text.rect.y;
	this->background.w = this->text.rect.w;
	this->background.h = this->text.rect.h;
}


void Button::updateTextColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer)
{
	this->text.updateColor(r, g, b, renderer);
}


void Button::destroy()
{
	this->text.destroy();
}


bool Button::isClicked(SDL_Event event) const
{
	if (event.button.button != SDL_BUTTON_LEFT)
		return false;

	if (
		event.button.x > this->background.x &&
		event.button.x < this->background.x + this->background.w &&
		event.button.y > this->background.y &&
		event.button.y < this->background.y + this->background.h
		)
		return true;

	return false;
}


bool Button::isHovered(SDL_Event event) const
{
	if (
		event.motion.x > this->background.x &&
		event.motion.x < this->background.x + this->background.w &&
		event.motion.y > this->background.y &&
		event.motion.y < this->background.y + this->background.h
		)
		return true;

	return false;
}


void Button::changeColorWhenHover(SDL_Event event, Uint8 r1, Uint8 g1, Uint8 b1, Uint8 r2, Uint8 g2, Uint8 b2, SDL_Renderer *renderer)
{
	if (this->isHovered(event))
	{
		this->updateBackgroundColor(r1, g1, b1);
		this->updateTextColor(r2, g2, b2, renderer);
	}
	else
	{
		this->updateBackgroundColor(r2, g2, b2);
		this->updateTextColor(r1, g1, b1, renderer);
	}
}