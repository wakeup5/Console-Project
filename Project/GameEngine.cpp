#include "GameEngine.h"

GameEngine::GameEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	this->buffer = new RenderBuffer(width, height);

	this->font = new Font();

	this->people = Image::LoadBmp("Resources/Images/people.bmp");
	this->tileSet = Image::LoadBmp("Resources/Images/Tileset.bmp");

	TiledSprite t(this->tileSet, 10, 10);
	this->map1 = TileMap("Resources/Maps/Map1.json", t);
	this->map5 = TileMap("Resources/Maps/Map5.json", t);

	this->tilemap = &this->map1;

	TiledSprite characters(this->people, 4, 2);
	TiledSprite character = TiledSprite::Create(characters.GetSprite(1, 0), 3, 4);
	this->player = Character(character);

	POINT p = this->tilemap->CellToWorld(this->tilemap->GetColumn() / 2, this->tilemap->GetRow() / 2);
	this->player.MoveTo(p);
}

void GameEngine::Release()
{
	delete buffer;

	delete people;
	delete tileSet;

	delete font;
}

void GameEngine::Update(float deltaTime)
{
	Input::BeginUpdate();

	float moveTime = 0.15f;

	Vector2 playerPos = this->player.GetPosIgnoreMove();
	POINT p = this->tilemap->WorldToCell(playerPos.x, playerPos.y);

	if (Input::IsKeyDown('A'))
	{
		this->player.SetDir(DIRECTION::LEFT);

		if (this->tilemap->IsMovable(p.x - 1, p.y))
		{
			POINT to = this->tilemap->CellToWorld(p.x - 1, p.y);
			this->player.MoveTo(to, moveTime);
		}
	}

	if (Input::IsKeyDown('D'))
	{
		this->player.SetDir(DIRECTION::RIGHT);
		
		if (this->tilemap->IsMovable(p.x + 1, p.y))
		{
			POINT to = this->tilemap->CellToWorld(p.x + 1, p.y);
			this->player.MoveTo(to, moveTime);
		}
	}

	if (Input::IsKeyDown('W'))
	{
		this->player.SetDir(DIRECTION::UP);
		
		if (this->tilemap->IsMovable(p.x, p.y - 1))
		{
			POINT to = this->tilemap->CellToWorld(p.x, p.y - 1);
			this->player.MoveTo(to, moveTime);
		}
	}

	if (Input::IsKeyDown('S'))
	{
		this->player.SetDir(DIRECTION::DOWN);
		
		if (this->tilemap->IsMovable(p.x, p.y + 1))
		{
			POINT to = this->tilemap->CellToWorld(p.x, p.y + 1);
			this->player.MoveTo(to, moveTime);
		}
	}

	TileMap::Teleporter t;
	if (this->tilemap->GetTeleporter(p.x, p.y, t))
	{
		POINT to = this->tilemap->CellToWorld(t.destX, t.destY);
		this->player.MoveTo(to);

		if (this->tilemap->GetID() != t.destID) 
		{
			if (t.destID == 1) 
			{
				this->tilemap = &this->map1;
			}
			else if (t.destID == 5)
			{
				this->tilemap = &this->map5;
			}
		}

	}

	this->player.Update(deltaTime);

	// tilemap error catch
	try 
	{
		int c = this->tilemap->GetColumn();
	}
	catch (int e)
	{
		this->tilemap = &this->map1;
		POINT p = this->tilemap->CellToWorld(this->tilemap->GetColumn() / 2, this->tilemap->GetRow() / 2);
		this->player.MoveTo(p);
	}
}

void GameEngine::Render()
{
	buffer->Clear(TEXT(' '));

	Vector2 playerPos = this->player.GetPos();
	this->tilemap->DrawTo(buffer, { (this->width / 2) - (int)round(playerPos.x) - 8, (this->height / 2) - (int)round(playerPos.y) - 8 });

	POINT p = (POINT)(-playerPos);
	p.x += this->width / 2 - 8;
	p.y += this->height / 2 - 8;

	this->player.DrawTo(buffer, p);
	//buffer->Rectangle('@', { 0, 0, 200, 32 });
	//this->font->DrawTo(buffer, { 0, 0, 200, 24 }, TEXT("안녕하세요. Waker입니다. 가나다라마바사~"));

	buffer->Render();
}
