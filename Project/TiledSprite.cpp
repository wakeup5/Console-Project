#include "TiledSprite.h"

TiledSprite::TiledSprite()
	: image(NULL)
	, col(0)
	, row(0)
	, rect()
	, cellWidth(0)
	, cellHeight(0)
{
}

TiledSprite::TiledSprite(Image* image, int col, int row)
	: TiledSprite(image, {0, 0, image->GetWidth(), image->GetHeight() }, col, row)
{

}

TiledSprite::TiledSprite(Image* image, const RECT& rect, int col, int row)
	: image(image)
	, col(col)
	, row(row)
	, rect(rect)
	, cellWidth(0)
	, cellHeight(0)
{
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	this->cellWidth = w / col;
	this->cellHeight = h / row;
}

void TiledSprite::DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum)
{
	if (this->image == NULL) 
	{
		return;
	}

	RECT rect = {
		this->rect.left + colNum * this->cellWidth,
		this->rect.top + rowNum * this->cellHeight,
		this->rect.left + (colNum + 1) * this->cellWidth,
		this->rect.top + (rowNum + 1) * this->cellHeight
	};

	buffer->Draw(this->image, pos, rect);
}

TiledSprite TiledSprite::Create(Image* image, int col, int row)
{
	return TiledSprite(image, col, row);
}

TiledSprite TiledSprite::Create(Image* image, int totalCol, int totalRow, int startCol, int startRow, int colLen, int rowLen)
{
	int width = image->GetWidth() / totalCol;
	int height = image->GetHeight() / totalRow;

	RECT rect = {
		width * startCol,
		height * startRow,
		width * (startCol + colLen),
		height * (startRow + rowLen)
	};

	return TiledSprite(image, rect, colLen, rowLen);
}

TiledSprite TiledSprite::Create(const Sprite& sprite, int col, int row)
{
	Sprite s(sprite);
	return TiledSprite(s.GetImage(), s.GetRect(), col, row);
}
