#pragma once

#include <Windows.h>

#define cimg_use_jpeg
//#define cimg_use_png
#include "CImg.h"
#include "RenderBuffer.h"

using namespace cimg_library;

class UnicodeImage
{
private:
	int width;
	int height;
	char* image;
public:
	UnicodeImage(const char* const filename, int width, int height);
	~UnicodeImage();

	void DrawTo(RenderBuffer* buffer, const POINT& pos);
	void DrawTo(RenderBuffer* buffer, const POINT& pos, const RECT& imageRect);
};

class UnicodeSprite : UnicodeImage
{
private:
	int col;
	int row;
	int cellWidth;
	int cellHeight;

public:
	UnicodeSprite(const char* const filename, int width, int height, int col, int row);

	void DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum);
};

