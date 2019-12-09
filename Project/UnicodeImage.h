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

