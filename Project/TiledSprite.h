#pragma once

#include <Windows.h>

#include "RenderBuffer.h"
#include "Image.h"

class TiledSprite
{
private:
	Image* image;
	int col;
	int row;
	int cellWidth;
	int cellHeight;

public:
	TiledSprite(Image* image, int col, int row);
	void DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum);
};

