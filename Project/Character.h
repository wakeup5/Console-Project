#pragma once
#include <Windows.h>
#include "Vector2.h"
#include "TiledSprite.h"

enum DIRECTION
{
	UP = 3,
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2
};

class Character
{
private:
	TiledSprite sprite;

	Vector2 start;
	Vector2 end;
	Vector2 pos;

	DIRECTION dir;

	float currentTime;
	float moveTime;

	float animationTime;

public:
	Character();
	Character(const TiledSprite& sprite);

	inline void SetDir(DIRECTION dir) { if (this->currentTime == 0) this->dir = dir; }
	void MoveTo(const Vector2& pos);
	void MoveTo(const Vector2& pos, float moveSpeed);
	void Update(float deltaTime);
	
	void DrawTo(RenderBuffer* buffer, const POINT& pos);

	inline Vector2 GetPos() 
	{ 
		return this->pos; 
	}

	inline Vector2 GetPosIgnoreMove()
	{
		if (this->currentTime != 0)
		{
			return this->start;
		}

		return this->pos;
	}
};

