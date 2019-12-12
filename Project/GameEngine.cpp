#include "GameEngine.h"

GameEngine::GameEngine(int width, int height)
{
	this->width = width;
	this->height = height;
	
	this->buffer = new RenderBuffer(width, height);

	this->font = new Font();

	this->people = Image::LoadBmp("people.bmp");
	this->tileSet = Image::LoadBmp("Tileset.bmp");

	this->dir = 0;
	this->anim = 0.0f;

	this->pos = { width / 2, height / 2 };
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

	if (Input::IsKeyDownOnce(VK_LEFT)) {
		this->dir = 1;
		this->pos.x -= 16;
	}
	else if (Input::IsKeyDownOnce(VK_RIGHT)) {
		this->dir = 2;
		this->pos.x += 16;
	}

	anim += deltaTime * 6.f;
}

void GameEngine::Render()
{
	buffer->Clear(TEXT('@'));

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


	TiledSprite tiles(this->tileSet, 8, 16);

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			tiles.DrawTo(buffer, { i * 16, j * 16 }, j % 3, i % 3);
		}
	}

	TiledSprite animation(this->people, 12, 8);
	animation.DrawTo(buffer, pos, col, dir);

	buffer->Rectangle('@', { 0, 0, 200, 32 });
	this->font->DrawTo(buffer, { 0, 0, 200, 24 }, TEXT("안녕하세요. Waker입니다. 가나다라마바사~"));

	buffer->Render();
}
