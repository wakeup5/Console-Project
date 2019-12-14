#include "Font.h"

//// �ʼ� ����Ʈ. 00 ~18
//TCHAR ChosungList[] = { 
//	'��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', 
//	'��', '��', '��', '��', '��', '��', '��', '��' };
//// �߼� ����Ʈ. 00 ~20
//TCHAR JungsungList[] = { 
//	'��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��',
//	'��', '��', '��', '��', '��', '��', '��', '��', '��', '��' };
////���� ����Ʈ. 00 ~27 + 1(1�� ����)
//TCHAR JongsungList[] = {
//	' ', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��',
//	'��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��',
//	'��', '��', '��', '��', '��', '��' };

Font::Font()
{
	// �ϵ��ڵ� �����Ŵ�
	this->asciiImage = Image::LoadBmp("Resources/Images/Ascii.bmp");
	this->asciiSprite = new TiledSprite(this->asciiImage, 20, 5);

	this->koreanImage = Image::LoadBmp("Resources/Images/Kor.bmp");
	this->koreanSprite = new TiledSprite(this->koreanImage, 10, 10);
}

Font::~Font()
{
	delete this->asciiImage;
	delete this->asciiSprite;
}

void Font::DrawTo(RenderBuffer* buffer, const RECT& rect, const TCHAR* text)
{
	int x = rect.left;
	int y = rect.top;

	int length = wcslen(text);
	
	for (int i = 0; i < length; i++) {
		TCHAR c = text[i];

		// ascii code
		if (c >= 0x20 && c < 0x7f) {

			if (x + asciiSprite->GetCellWidth() > rect.right) {
				x = rect.left;
				y += asciiSprite->GetCellHeight();
			}

			if (y > rect.bottom) {
				break;
			}

			int index = c - 0x20;
			int cx = index % asciiSprite->GetColumn();
			int cy = index / asciiSprite->GetColumn();

			Sprite charSpr = asciiSprite->GetSprite(cx, cy);
			charSpr.DrawTo(buffer, { x, y });
			x += asciiSprite->GetCellWidth();
		}
		// korean
		else if (c >= 0xac00 && c < 0xd7a4) {

			if (x + koreanSprite->GetCellWidth() > rect.right) {
				x = rect.left;
				y += koreanSprite->GetCellHeight();
			}

			if (y > rect.bottom) {
				break;
			}

			// �������� ����
			int in_char = c - 0xAC00;
			int cho = in_char / (0x0015 * 0x001C);
			int jung = (in_char / 0x001C) % 0x0015;
			int jong = in_char % 0x001C;

			if (jung >= 8 && jung < 20) {
				cho += 20;
			}

			koreanSprite->DrawTo(buffer, { x, y }, cho % 10, cho / 10);
			koreanSprite->DrawTo(buffer, { x, y }, jung % 10, (jung / 10) + 4);
			koreanSprite->DrawTo(buffer, { x, y }, jong % 10, (jong / 10) + 7);
			x += koreanSprite->GetCellWidth();
		}
		// korean ��,����
		else if (c >= 0x3130 && c <= 0x314F) {
			if (x + koreanSprite->GetCellWidth() > rect.right) {
				x = rect.left;
				y += koreanSprite->GetCellHeight();
			}

			if (y > rect.bottom) {
				break;
			}

			koreanSprite->DrawTo(buffer, { x, y }, 0, 0);
			x += koreanSprite->GetCellWidth();
		}
		// �ƽ�Ű + �ѱ� �ܿ��� �ƹ��͵� �׸��� �ʴ´�.
		else {
			if (x + 8 > rect.right) {
				x = rect.left;
				y += 16;
			}

			if (y > rect.bottom) {
				break;
			}

			x += 8;
		}
	}
}
