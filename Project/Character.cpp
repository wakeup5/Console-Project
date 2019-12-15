#include "Character.h"


Character::Character()
	: sprite()
	, start()
	, end()
	, moveTime(0.f)
	, currentTime(0.f)
	, dir(DIRECTION::DOWN)
	, animationTime(0.f)
{
}

Character::Character(const TiledSprite& sprite)
	:sprite(sprite)
	, start()
	, end()
	, moveTime(0.f)
	, currentTime(0.f)
	, dir(DIRECTION::DOWN)
	, animationTime(0.f)
{
}

void Character::MoveTo(const Vector2& pos)
{
	this->pos = pos;
	this->currentTime = 0.f;
}

void Character::MoveTo(const Vector2& pos, float moveTime)
{
	if (this->currentTime != 0.f)
	{
		return;
	}

	this->start = this->pos;
	this->end = pos;
	this->moveTime = moveTime;
	this->currentTime = moveTime;
}

void Character::Update(float deltaTime)
{
	if (this->currentTime > 0)
	{
		this->currentTime -= deltaTime;

		float t = 1 - (this->currentTime / this->moveTime);
		this->pos = Vector2::Lerp(this->start, this->end, t);

		this->animationTime += deltaTime;
	}
	else if (this->currentTime < 0)
	{
		this->pos = this->end;
		this->currentTime = 0.f;
	}
}

void Character::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
	POINT p;
	p.x = (int)(round(this->pos.x)) + pos.x;
	p.y = (int)(round(this->pos.y)) + pos.y;

	if (this->currentTime == 0 || this->moveTime == 0)
	{
		this->sprite.DrawTo(buffer, p, 1, int(this->dir));
		return;
	}

	int t = int(round(this->animationTime * 16)) % 4;
	int a = 0;
	switch (t)
	{
	case 0:
		a = 0;
		break;
	case 1:
	case 3:
		a = 1;
		break;
	case 2:
		a = 2;
		break;
	}

	this->sprite.DrawTo(buffer, p, a, int(this->dir));
}
