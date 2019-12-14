#include "TiledSprite.h"

TiledSprite::TiledSprite()
	: image(NULL)
	, col(0)
	, row(0)
	, cellWidth(0)
	, cellHeight(0)
{
}

TiledSprite::TiledSprite(Image* image, int col, int row)
	: image(image)
	, col(col)
	, row(row)
	, cellWidth(0)
	, cellHeight(0)
{
	this->cellWidth = this->image->GetWidth() / col;
	this->cellHeight = this->image->GetHeight() / row;
}

void TiledSprite::DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum)
{
	if (this->image == NULL) 
	{
		return;
	}

	RECT rect = {
		colNum * this->cellWidth,
		rowNum * this->cellHeight,
		(colNum + 1) * this->cellWidth,
		(rowNum + 1) * this->cellHeight
	};

	buffer->Draw(this->image, pos, rect);
}
