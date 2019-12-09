#include "Sprite.h"

Sprite::Sprite(UnicodeImage* image, const RECT& rect) 
	:image(image)
	,rect(rect)
{
}

void Sprite::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
	image->DrawTo(buffer, pos, this->rect);
}
