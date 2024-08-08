#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"
#include "Vector2.h"


enum Direction
{
	LEFT,
	RIGHT
};


class Player : public Object
{
	public:
		Vector2 velocity = {0, 0};
		bool isOnFloor = false;
		int gravity = -5;

		Player(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) : Object(x, y, w, h, r, g, b) {};
		void move(Direction direction);
		void jump();
		void update(std::vector<Object> &objects);
		void checkObjectCollision(std::vector<Object> &objects);
};