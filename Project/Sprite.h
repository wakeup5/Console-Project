#pragma once

#include <Windows.h>

#include "RenderBuffer.h"
#include "Image.h"

class Sprite
{
private:
	Image* image;
	RECT rect;

public:
	Sprite(Image* image);
	Sprite(Image* image, const RECT& rect);
	
	inline Image* GetImage() { return this->image; }

	inline RECT GetRect() { return this->rect; }
	void DrawTo(RenderBuffer* buffer, const POINT& pos);
};

