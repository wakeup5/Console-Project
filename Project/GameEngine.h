#pragma once

#include "RenderBuffer.h"
#include "Image.h"
#include "Sprite.h"
#include "TiledSprite.h"
#include "Font.h"
#include "Input.h"
#include "Log.h"
#include "TileMap.h"
#include "Vector2.h"
#include "Character.h"

class GameEngine
{
private:
	int width;
	int height;

	RenderBuffer* buffer;

	Font* font;

	Image* people;
	Image* tileSet;

	TileMap* tilemap;
	TileMap map1;
	TileMap map5;

	Character player;

	bool exit;
public:
	GameEngine(int width, int height);
	void Release();
	void Update(float deltaTime);
	void Render();

	inline bool IsExit() { return exit; }
};

