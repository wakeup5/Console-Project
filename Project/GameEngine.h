#pragma once

#include "RenderBuffer.h"
#include "Image.h"
#include "Sprite.h"
#include "TiledSprite.h"
#include "Font.h"
#include "Input.h"
#include "Log.h"
#include "TileMap.h"

class GameEngine
{
private:
	int width;
	int height;

	RenderBuffer* buffer;

	Font* font;

	Image* people;
	Image* tileSet;

	TileMap tilemap;

	float dir;
	float anim;

	float posX;
	float posY;

	bool exit;
public:
	GameEngine(int width, int height);
	void Release();
	void Update(float deltaTime);
	void Render();

	bool inline IsExit() { return exit; }
};

