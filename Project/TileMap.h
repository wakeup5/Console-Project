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
		int x;
		int y;

		int tileID;

		int destID;
		int destX;
		int destY;
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

	inline int GetID() { return this->id; }
	inline int GetColumn() { return this->col; }
	inline int GetRow() { return this->row; }
	inline POINT CellToWorld(int x, int y) { return { x * this->tileWidth, y * this->tileHeight }; }
	inline POINT WorldToCell(int x, int y) { return { x / this->tileWidth, y / this->tileHeight }; }
	inline bool IsMovable(int x, int y) { return movable[y * this->col + x]; }

	bool GetTeleporter(int x, int y, OUT Teleporter& output);

	void DrawTo(RenderBuffer* buffer, const POINT& pos);
};

