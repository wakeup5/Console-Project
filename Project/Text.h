#pragma once

#include <Windows.h>
#include "Image.h"
#include "TiledSprite.h"

class Text
{
private:
	Image* asciiImage;
	TiledSprite* asciiSprite;

	Image* koreanImage;
	TiledSprite* koreanSprite;

public:
	Text();
	~Text();

	void DrawTo(RenderBuffer* buffer, const RECT& rect, const TCHAR* text);
};

