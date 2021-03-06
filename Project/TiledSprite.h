#pragma once

#include <Windows.h>

#include "RenderBuffer.h"
#include "Image.h"
#include "Sprite.h"

class TiledSprite
{
private:
	Image* image;
	RECT rect;
	int col;
	int row;
	int cellWidth;
	int cellHeight;
	
public:
	TiledSprite();
	TiledSprite(Image* image, int col, int row);
	TiledSprite(Image* image, const RECT& rect, int col, int row);
	void DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum);

	static TiledSprite Create(Image* image, int col, int row);
	static TiledSprite Create(Image* image, int totalCol, int totalRow, int startCol, int startRow, int colLen, int rowLen);
	static TiledSprite Create(const Sprite& sprite, int col, int row);

	inline int GetColumn() { return this->col; }
	inline int GetRow() { return this->row; }
	inline int GetCellWidth() { return this->cellWidth; }
	inline int GetCellHeight() { return this->cellHeight; }
	inline Sprite GetSprite(int x, int y) 
	{
		RECT rect = {
		   x * this->cellWidth,
		   y * this->cellHeight,
		   (x + 1) * this->cellWidth,
		   (y + 1) * this->cellHeight
		};
		return Sprite(image, rect); 
	}
};

