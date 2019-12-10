#pragma once

#include <windows.h>

#include "Image.h"

class RenderBuffer
{
private:
	CHAR_INFO* buffer;
	int width;
	int height;

	bool hasChanges;

public:
	RenderBuffer(int width, int height);
	~RenderBuffer();

	bool inline HasChanges() {
		return hasChanges;
	}

	void Draw(Image* data, const POINT& leftTop);
	void Draw(Image* data, const POINT& leftTop, const RECT& imageRect);
	void Clear(TCHAR c);
	void Rectangle(TCHAR c, const RECT& rect);
	void Render();
};

