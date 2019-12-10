#pragma once

#include <Windows.h>

//#define cimg_use_jpeg
//#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;

class Image
{
private:
	int width;
	int height;
	const TCHAR* const image;
	const bool* const mask;

	Image();
	Image(TCHAR* image, bool* mask, int width, int height);
public:
	~Image();

	inline int GetWidth() { return this->width; }
	inline int GetHeight() { return this->height; }

	inline TCHAR GetPixel(int x, int y) { return this->image[y * this->width + x]; }
	inline bool GetMask(int x, int y) { return this->mask[y * this->width + x]; }

	static Image* LoadBmp(const char* filename);
	static Image* LoadBmp(const char* filename, int width, int height);
	static Image* FromText(const char* text, int width, int height);
};