#include "GameEngine.h"

GameEngine::GameEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	this->buffer = new RenderBuffer(width, height);

	this->font = new Font();

	this->people = Image::LoadBmp("Resources/Images/people.bmp");
	this->tileSet = Image::LoadBmp("Resources/Images/Tileset.bmp");

	this->dir = 0;
	this->anim = 0.0f;

	TiledSprite t(this->tileSet, 10, 10);
	this->tilemap = TileMap("Resources/Maps/Map1.json", t);

	this->posX = tilemap.GetColumn() * 16 / 2;
	this->posY = tilemap.GetRow() * 16 / 2;
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

	if (Input::IsKeyDown(VK_LEFT)) 
	{
		this->dir = 1;
		this->posX -= 48 * deltaTime;
	}
	
	if (Input::IsKeyDown(VK_RIGHT)) 
	{
		this->dir = 2;
		this->posX += 48 * deltaTime;
	}
	
	if (Input::IsKeyDown(VK_UP)) 
	{
		this->dir = 3;
		this->posY -= 48 * deltaTime;
	}
	
	if (Input::IsKeyDown(VK_DOWN)) 
	{
		this->dir = 0;
		this->posY += 48 * deltaTime;
	}

	anim += deltaTime * 6.f;
}

void GameEngine::Render()
{
	buffer->Clear(TEXT('@'));

	this->tilemap.DrawTo(buffer, { (this->width / 2) - (int)round(this->posX), (this->height / 2) - (int)round(this->posY) });

	int col = 0;
	switch ((int)round(anim) % 4) {
	case 0:
	case 2:
		col = 1;
		break;
	case 1:
		col = 0;
		break;
	case 3:
		col = 2;
		break;
	}

	TiledSprite characters(this->people, 4, 2);

	TiledSprite animation = TiledSprite::Create(characters.GetSprite(1, 0), 3, 4);
	animation.DrawTo(buffer, { (this->width / 2) - 8, (this->height / 2) - 8 }, col, dir);

	//buffer->Rectangle('@', { 0, 0, 200, 32 });
	//this->font->DrawTo(buffer, { 0, 0, 200, 24 }, TEXT("안녕하세요. Waker입니다. 가나다라마바사~"));

	buffer->Render();
}
