#include "Text.h"


Text::Text()
{
	this->color = {0, 0, 0};
	this->rect = {0, 0, 0, 0};
}


Text::Text(std::string fontFilePath, int fontSize, Uint8 r, Uint8 g, Uint8 b, std::string text, int x, int y, SDL_Renderer *renderer)
{
	this->font = TTF_OpenFont("resources/font.ttf", fontSize);
	this->color = {r, g, b, 255};
	this->text = text;
	SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
	this->texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	this->rect = {x, y, fontSurface->w, fontSurface->h};
	SDL_FreeSurface(fontSurface);
}


void Text::updateText(std::string text, SDL_Renderer* renderer)
{
	this->text = text;
	SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
	SDL_DestroyTexture(this->texture);
	this->texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	this->rect.w = fontSurface->w;
	this->rect.h = fontSurface->h;
	SDL_FreeSurface(fontSurface);
}


void Text::updateColor(Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;

	SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
	SDL_DestroyTexture(this->texture);
	this->texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	this->rect.w = fontSurface->w;
	this->rect.h = fontSurface->h;
	SDL_FreeSurface(fontSurface);
}


void Text::center()
{
	this->rect.x = constants::WINDOW_WIDTH / 2 - this->rect.w / 2;
}


void Text::destroy()
{
	TTF_CloseFont(this->font);
	this->font = NULL;
	SDL_DestroyTexture(this->texture);
	this->texture = NULL;
}