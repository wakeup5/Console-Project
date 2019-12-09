#pragma once

#include <windows.h>
#include <iostream>
#include <string.h>

class RenderBuffer
{
private:
	CHAR_INFO* buffer;
	int width;
	int height;

	bool hasChanges;

public:
	struct ImageData
	{
		char const* Data;
		int imageWidth;
		int imageHeight;
	};

	RenderBuffer(int width, int height);
	~RenderBuffer();

	bool inline HasChanges() {
		return hasChanges;
	}

	void Draw(const ImageData& data, const POINT& leftTop);
	void Draw(const ImageData& data, const POINT& leftTop, const RECT& imageRect);
	void Clear(char c);
	void Render();

	
};

