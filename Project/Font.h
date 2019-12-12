#pragma once

#include <Windows.h>
#include "Image.h"
#include "TiledSprite.h"

class Font
{
private:
	Image* asciiImage;
	TiledSprite* asciiSprite;

	Image* koreanImage;
	TiledSprite* koreanSprite;

public:
	Font();
	~Font();

	void DrawTo(RenderBuffer* buffer, const RECT& rect, const TCHAR* text);
};

