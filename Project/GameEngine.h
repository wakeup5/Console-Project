#pragma once

#include "RenderBuffer.h"
#include "Image.h"
#include "Sprite.h"
#include "TiledSprite.h"
#include "Font.h"
#include "Input.h"

class GameEngine
{
private:
	int width;
	int height;

	RenderBuffer* buffer;

	Font* font;

	Image* people;
	Image* tileSet;

	float dir;
	float anim;

	POINT pos;

	bool exit;
public:
	GameEngine(int width, int height);
	void Release();
	void Update(float deltaTime);
	void Render();

	bool inline IsExit() { return exit; }
};

