#include "GameEngine.h"

GameEngine::GameEngine(int width, int height)
{
	this->width = width;
	this->height = height;
	
	this->buffer = new RenderBuffer(width, height);

	this->people = Image::LoadBmp("people.bmp");
	this->tileSet = Image::LoadBmp("Tileset.bmp");

	this->dir = 0;
	this->anim = 0.0f;
}

void GameEngine::Release()
{
	delete people;
	delete tileSet;
	delete buffer;
}

void GameEngine::Update(float deltaTime)
{
	dir += deltaTime * 2.f;
	anim += deltaTime * 6.f;
}

void GameEngine::Render()
{
	buffer->Clear('@');

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

	int x = (width / 2) + (cos(dir) * 40);
	int y = (height / 2) + (sin(dir) * 40);

	float angle = atan2(y, x);
	int d = 0;
	if (angle > 0.125f && angle <= 0.375f) {
		d = 0;
	}
	else if (angle > 0.375f && angle <= 0.625f) {
		d = 1;
	}
	else if (angle > 0.625f && angle <= 0.875f) {
		d = 2;
	}
	else {
		d = 3;
	}

	POINT pos = { x - 8, y - 8 };

	TiledSprite animation(this->people, 12, 8);
	animation.DrawTo(buffer, pos, col, d);

	TiledSprite tiles(this->tileSet, 8, 16);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tiles.DrawTo(buffer, { i * 16, j * 16 }, j, i);
		}
	}

	buffer->Render();
}
