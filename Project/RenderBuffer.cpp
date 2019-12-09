#include "RenderBuffer.h"

using namespace std;

RenderBuffer::RenderBuffer(int width, int height)
	:width(width),
	height(height)
{
	this->buffer = new CHAR_INFO[this->width * height];
	Clear(' ');
}

RenderBuffer::~RenderBuffer()
{
	delete[] this->buffer;
	this->buffer = NULL;
}

void RenderBuffer::Draw(const ImageData& data, const POINT& leftTop)
{
	const int left = leftTop.x;
	const int top = leftTop.y;
	const int width = data.imageWidth;
	const int height = data.imageHeight;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int dx = x + left;
			int dy = y + top;

			if (dx < 0 || dx >= this->width || dy < 0 || dy >= this->height) {
				continue;
			}

			int sIndex = y * width + x;
			int dIndex = dy * this->width + dx;

			buffer[dIndex].Char.UnicodeChar = data.Data[sIndex];
		}
	}

	hasChanges = true;
}

void RenderBuffer::Draw(const ImageData& data, const POINT& leftTop, const RECT& imageRect)
{
	const int left = leftTop.x;
	const int top = leftTop.y;
	const int width = min(data.imageWidth, imageRect.right) - imageRect.left;
	const int height = min(data.imageHeight, imageRect.bottom) - imageRect.top;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int sx = x + imageRect.left;
			int sy = y + imageRect.top;
			int dx = x + left;
			int dy = y + top;

			if (dx < 0 || dx >= this->width || dy < 0 || dy >= this->height) {
				continue;
			}

			int sIndex = sy * data.imageWidth + sx;
			int dIndex = dy * this->width + dx;

			buffer[dIndex].Char.UnicodeChar = data.Data[sIndex];
		}
	}

	hasChanges = true;
}

void RenderBuffer::Clear(char c)
{
	for (int i = 0; i < this->width * height; i++) {
		this->buffer[i].Char.UnicodeChar = c;
		this->buffer[i].Attributes = 7;
	}

	hasChanges = true;
}

void RenderBuffer::Render()
{
	if (!hasChanges) {
		return;
	}

	COORD null = { 0, 0 }, size = { this->width, this->height };
	SMALL_RECT rect = { 0, 0, this->width, this->height };
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), this->buffer, size, null, &rect);
}
