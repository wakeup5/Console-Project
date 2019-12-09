#pragma once

#include "RenderBuffer.h"
#include "UnicodeImage.h"
#include "Sprite.h"
#include "TiledSprite.h"

class GameEngine
{
private:
	int width;
	int height;

	RenderBuffer* buffer;
	UnicodeImage* image;// ("people.jpg", 192, 128, 12, 8);
	Sprite* tile;
	TiledSprite* animation;

	int direction;
	float anim;

	bool exit;
public:
	GameEngine(int width, int height);
	void Release();
	void Update(float deltaTime);
	void Render();

	bool inline IsExit() { return exit; }
};

