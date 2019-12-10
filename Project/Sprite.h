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
	void DrawTo(RenderBuffer* buffer, const POINT& pos);
};

