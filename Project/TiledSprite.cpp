#include "TiledSprite.h"

TiledSprite::TiledSprite(UnicodeImage* image, int col, int row)
	:image(image)
	,col(col)
	,row(row)
{
	this->cellWidth = this->image->GetWidth() / col;
	this->cellHeight = this->image->GetHeight() / row;
}

void TiledSprite::DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum)
{
	RECT rect = {
		colNum * this->cellWidth,
		rowNum * this->cellHeight,
		(colNum + 1) * this->cellWidth,
		(rowNum + 1) * this->cellHeight
	};

	image->DrawTo(buffer, pos, rect);
}
