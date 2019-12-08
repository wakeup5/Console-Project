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

public:
	RenderBuffer(int width, int height);
	~RenderBuffer();

	void Clear(char c);
	void Draw();
};

