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

void RenderBuffer::Draw(Image* data, const POINT& leftTop)
{
	const int left = leftTop.x;
	const int top = leftTop.y;
	const int width = data->GetWidth();
	const int height = data->GetHeight();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int dx = x + left;
			int dy = y + top;

			if (dx < 0 || dx >= this->width || dy < 0 || dy >= this->height) {
				continue;
			}

			//int sIndex = y * width + x;
			int dIndex = dy * this->width + dx;

			if (!data->GetMask(x, y)) {
				continue;
			}

			buffer[dIndex].Char.UnicodeChar = data->GetPixel(x, y);
		}
	}

	hasChanges = true;
}

void RenderBuffer::Draw(Image* data, const POINT& leftTop, const RECT& imageRect)
{
	const int left = leftTop.x;
	const int top = leftTop.y;
	const int width = min(data->GetWidth(), imageRect.right) - imageRect.left;
	const int height = min(data->GetHeight(), imageRect.bottom) - imageRect.top;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int sx = x + imageRect.left;
			int sy = y + imageRect.top;
			int dx = x + left;
			int dy = y + top;

			if (dx < 0 || dx >= this->width || dy < 0 || dy >= this->height) {
				continue;
			}

			//int sIndex = sy * data.imageWidth + sx;
			int dIndex = dy * this->width + dx;
			
			if (!data->GetMask(sx, sy)) {
				continue;
			}

			buffer[dIndex].Char.UnicodeChar = data->GetPixel(sx, sy);
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
