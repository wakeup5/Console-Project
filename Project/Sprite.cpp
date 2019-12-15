#include "Sprite.h"

Sprite::Sprite(Image* image)
	:image(image)
{
	this->rect = RECT{
		0,
		0,
		image->GetWidth(),
		image->GetHeight()
	};

}

Sprite::Sprite(Image* image, const RECT& rect)
	:image(image)
	,rect(rect)
{
}

void Sprite::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
	buffer->Draw(this->image, pos, rect);
}
//void Image::DrawTo(RenderBuffer* buffer, const POINT& pos)
//{
//    RenderBuffer::ImageData data;
//    data.image = image;
//    data.mask = mask;
//    data.imageWidth = this->width;
//    data.imageHeight = this->height;
//
//    buffer->Draw(data, pos);
//}
//
//void Image::DrawTo(RenderBuffer* buffer, const POINT& pos, const RECT& imageRect)
//{
//    RenderBuffer::ImageData data;
//    data.image = image;
//    data.mask = mask;
//    data.imageWidth = this->width;
//    data.imageHeight = this->height;
//
//    buffer->Draw(data, pos, imageRect);
//}