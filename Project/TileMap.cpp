#include "TileMap.h"

using json = nlohmann::json;
using namespace std;

TileMap::TileMap()
	:id(-1)
	,col(0)
	,row(0)
	,tileHeight(0)
	,tileWidth(0)
	,tile()
	,movable()
	,teleporter()
{

}

TileMap::TileMap(const char* jsonfile, const TiledSprite& tileset)
{
	ifstream f(jsonfile);
	json j;

	f >> j;

	this->id = j["properties"]["ID"];

	this->col = j["width"];
	this->row = j["height"];

	this->tileWidth = j["tilewidth"];
	this->tileHeight = j["tileheight"];

	// layers
	// layer 번호는 하드코딩
	vector<int> t = j["layers"][0]["data"];
	this->tile = vector<int>(t);

	vector<int> m = j["layers"][1]["data"];
	this->movable = vector<int>(m);

	// teleporter
	for (int i = 0; i < j["layers"][2].count("objects"); i++) 
	{
		json obj = j["layers"][2]["objects"][i];
		Teleporter t;
		t.id = obj["properties"]["TeleportMap"];
		t.x = obj["properties"]["TeleportX"];
		t.y = obj["properties"]["TeleportY"];

		this->teleporter.push_back(t);
	}

	this->sprite = tileset;
}

TileMap::~TileMap()
{

}

void TileMap::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
	for (int i = 0; i < this->tile.size(); i++) 
	{
		int num = this->tile[i] - 1;

		if (num < 0) 
		{
			continue;
		}

		int x = i % this->col;
		int y = i / this->col;

		int tileX = num % this->sprite.GetColumn();
		int tileY = num / this->sprite.GetColumn();

		POINT offset;
		offset.x = pos.x + (x * this->tileWidth);
		offset.y = pos.y + (y * this->tileHeight);

		this->sprite.DrawTo(buffer, offset, tileX, tileY);
	}
}
