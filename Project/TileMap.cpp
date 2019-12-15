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
		t.destID = obj["properties"]["TeleportMap"];
		t.destX = obj["properties"]["TeleportX"];
		t.destY = obj["properties"]["TeleportY"];

		t.tileID = obj["properties"]["TIle"];

		t.x = obj["x"] / this->tileWidth;
		t.y = (obj["y"] / this->tileHeight) - 1; // 

		this->teleporter.push_back(t);
	}

	this->sprite = tileset;
}

TileMap::~TileMap()
{

}

bool TileMap::GetTeleporter(int x, int y, OUT Teleporter& output)
{
	for (int i = 0; i < this->teleporter.size(); i++)
	{
		Teleporter t = this->teleporter[i];
		if (t.x == x && t.y == y)
		{
			output = t;
			return true;
		}
	}

	return false;
}

void TileMap::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
	for (int i = 0; i < this->tile.size(); i++) 
	{
		int num = (this->tile[i] % 100) - 1;

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

	for (int i = 0; i < this->teleporter.size(); i++) 
	{
		Teleporter t = this->teleporter[i];

		int tileX = t.tileID % this->sprite.GetColumn();
		int tileY = t.tileID / this->sprite.GetColumn();

		POINT offset;
		offset.x = pos.x + (t.x * this->tileWidth);
		offset.y = pos.y + (t.y * this->tileHeight);

		this->sprite.DrawTo(buffer, offset, tileX, tileY);
	}
}
