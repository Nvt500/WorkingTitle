#include "Object.h"


Object::Object(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = 255;
}


bool Object::checkPlayerCollision(Object obj) const
{
	if (
		this->rect.x < obj.rect.x + obj.rect.w &&
		this->rect.x + this->rect.w > obj.rect.x &&
		this->rect.y < obj.rect.y + obj.rect.h &&
		this->rect.y + this->rect.h > obj.rect.y
		)
		return true;

	return false;
}