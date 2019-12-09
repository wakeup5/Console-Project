#include "GameEngine.h"

GameEngine::GameEngine(int width, int height)
{
	this->width = width;
	this->height = height;
	this->image = new UnicodeImage("people.bmp", 192, 128);
	this->tile = new Sprite(this->image, { 0, 0, 16, 16 });
	this->animation = new TiledSprite(this->image, 12, 8);
	this->buffer = new RenderBuffer(width, height);

	this->direction = 0;
	this->anim = 0.0f;
}

void GameEngine::Release()
{
	delete image;
	delete buffer;
}

void GameEngine::Update(float deltaTime)
{
	anim += deltaTime * 6.f;
}

void GameEngine::Render()
{
	buffer->Clear('-');

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

	this->tile->DrawTo(buffer, { 0, 0 });
	POINT pos = { (width - 16) / 2, (height - 16) / 2 };
	this->animation->DrawTo(buffer, pos, col, direction);

	buffer->Render();
}
