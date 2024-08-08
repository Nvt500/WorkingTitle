#include "Player.h"
#include "constants.h"


void Player::move(Direction direction)
{
	switch (direction)
	{
		case LEFT:
			this->velocity.x -= 4;
			break;

		case RIGHT:
			this->velocity.x += 4;
			break;

		default:
			break;
	}
}


void Player::jump()
{
	if (this->isOnFloor)
		this->velocity.y = -11;
}


void Player::update(std::vector<Object> &objects)
{
	// SELF EXPLANITORY
	this->checkObjectCollision(objects);
	
	// UPDATE POSITION
	this->rect.x += this->velocity.x;
	this->rect.y += this->velocity.y;
	
	// SCREEN BOUNDS
	if (this->rect.x < 0)
		this->rect.x = 0;
	if (this->rect.x + this->rect.w > constants::WINDOW_WIDTH)
		this->rect.x = constants::WINDOW_WIDTH - this->rect.w;
	if (this->rect.y < 0)
		this->rect.y = 0;
	if (this->rect.y + this->rect.h > constants::WINDOW_HEIGHT)
	{
		this->rect.y = constants::WINDOW_HEIGHT - this->rect.h;
		this->isOnFloor = true;
	}
	else if (this->velocity.y != 0)
		this->isOnFloor = false;

	// VELOCITY DECAY
	if (!isOnFloor)
	{
		if (this->velocity.y < 0)
			this->velocity.y++;
		else if (this->velocity.y < 10)
			this->velocity.y += 2;
	}
	else
		this->velocity.y = 1;
	this->velocity.x = 0;
}


void Player::checkObjectCollision(std::vector<Object> &objects)
{

	// X
	bool exit = true;
	while (this->velocity.x != 0 && exit)
	{
		for (const Object &obj : objects)
		{
			if (
				this->rect.x + this->velocity.x < obj.rect.x + obj.rect.w &&
				this->rect.x + this->velocity.x + this->rect.w > obj.rect.x &&
				this->rect.y < obj.rect.y + obj.rect.h &&
				this->rect.y + this->rect.h > obj.rect.y
				)
			{
				if (this->velocity.x > 0)
					this->velocity.x--;
				else
					this->velocity.x++;

				break;
			}
			if (&obj == &objects.back())
				exit = false;
		}
	}

	// Y
	exit = true;
	while (this->velocity.y != 0 && exit)
	{
		for (const Object& obj : objects)
		{
			if (
				this->rect.x < obj.rect.x + obj.rect.w &&
				this->rect.x + this->rect.w > obj.rect.x &&
				this->rect.y + this->velocity.y < obj.rect.y + obj.rect.h &&
				this->rect.y + this->velocity.y + this->rect.h > obj.rect.y
				)
			{
				if (this->velocity.y > 0)
					this->velocity.y--;
				else
					this->velocity.y++;

				if (this->velocity.y > 0)
					this->isOnFloor = true;

				break;
			}
			if (&obj == &objects.back())
				exit = false;
		}
	}

	// X & Y (CORNERS)
	exit = true;
	while (this->velocity.x != 0 && this->velocity.y != 0 && exit)
	{
		for (const Object& obj : objects)
		{
			if (
				this->rect.x + this->velocity.x < obj.rect.x + obj.rect.w &&
				this->rect.x + this->velocity.x + this->rect.w > obj.rect.x &&
				this->rect.y + this->velocity.y < obj.rect.y + obj.rect.h &&
				this->rect.y + this->velocity.y + this->rect.h > obj.rect.y
				)
			{
				if (this->velocity.x > 0)
					this->velocity.x--;
				else
					this->velocity.x++;

				if (this->velocity.y > 0)
					this->velocity.y--;
				else
					this->velocity.y++;

				if (this->velocity.y > 0)
					this->isOnFloor = true;

				break;
			}
			if (&obj == &objects.back())
				exit = false;
		}
	}
}