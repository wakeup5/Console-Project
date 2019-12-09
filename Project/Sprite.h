#pragma once

#include <Windows.h>

#include "RenderBuffer.h"
#include "UnicodeImage.h"

class Sprite
{
private:
	UnicodeImage* image;
	RECT rect;

public:
	Sprite(UnicodeImage* image, const RECT& rect);
	void DrawTo(RenderBuffer* buffer, const POINT& pos);
};

