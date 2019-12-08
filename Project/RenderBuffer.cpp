#include "RenderBuffer.h"

using namespace std;

RenderBuffer::RenderBuffer(int width, int height)
	:width(width * 2),
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

void RenderBuffer::Clear(char c)
{
	for (int i = 0; i < this->width * height; i++) {
		this->buffer[i].Char.UnicodeChar = c;
		this->buffer[i].Attributes = 7;
	}
}

void RenderBuffer::Draw()
{
	COORD null = { 1, 1 }, size = { this->width, this->height };
	SMALL_RECT rect = { 0, 0, this->width, this->height };
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), this->buffer, size, null, &rect);

	////SetCursorPos(0, 0);
	//COORD p = { 0, 0 };
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	//
	//for (int h = 0; h < this->height; h++) {
	//	char* str = new char[width + 1];
	//	for (int w = 0; w < this->width; w++) {
	//		str[w] = this->buffer[h * height + w];
	//	}
	//	str[width] = '\0';
	//	cout << str << endl;
	//}
}
