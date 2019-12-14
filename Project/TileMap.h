#pragma once

#include <fstream>
#include <vector>
#include "TiledSprite.h"
#include "RenderBuffer.h"
#include "json.hpp"

class TileMap
{
public:
	struct Teleporter
	{
		int id;
		int x;
		int y;
	};

private:
	int id;
	std::vector<int> tile;
	std::vector<int> movable;
	int col;
	int row;
	int tileWidth;
	int tileHeight;
	std::vector<Teleporter> teleporter;
	TiledSprite sprite;
public:
	TileMap();
	TileMap(const char* jsonfile, const TiledSprite& tileset);
	~TileMap();

	void DrawTo(RenderBuffer* buffer, const POINT& pos);
};

