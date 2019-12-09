#pragma once

#include <Windows.h>

#include "UnicodeImage.h";
#include "RenderBuffer.h"

class TiledSprite
{
private:
	UnicodeImage* image;
	int col;
	int row;
	int cellWidth;
	int cellHeight;

public:
	TiledSprite(UnicodeImage* image, int col, int row);
	void DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum);
};

