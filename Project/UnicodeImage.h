#pragma once

#include <Windows.h>

//#define cimg_use_jpeg
//#define cimg_use_png
#include "CImg.h"
#include "RenderBuffer.h"

using namespace cimg_library;

class UnicodeImage
{
private:
	int width;
	int height;
	TCHAR* image;
	bool* mask;

public:
	UnicodeImage(const char* filename);
	UnicodeImage(const char* filename, int width, int height);
	~UnicodeImage();

	void DrawTo(RenderBuffer* buffer, const POINT& pos);
	void DrawTo(RenderBuffer* buffer, const POINT& pos, const RECT& imageRect);

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }

	TCHAR GetPixel(int x, int y) { return this->image[y * this->width + x]; }
	bool GetMask(int x, int y) { return this->mask[y * this->width + x]; }
};
//
//class UnicodeSprite : UnicodeImage
//{
//private:
//	int col;
//	int row;
//	int cellWidth;
//	int cellHeight;
//
//public:
//	UnicodeSprite(const char* const filename, int width, int height, int col, int row);
//
//	void DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum);
//};
//
