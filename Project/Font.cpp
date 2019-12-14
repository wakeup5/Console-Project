#include "Font.h"

//// 초성 리스트. 00 ~18
//TCHAR ChosungList[] = { 
//	'ㄱ', 'ㄲ', 'ㄴ', 'ㄷ', 'ㄸ', 'ㄹ', 'ㅁ', 'ㅂ', 'ㅃ', 'ㅅ', 'ㅆ', 
//	'ㅇ', 'ㅈ', 'ㅉ', 'ㅊ', 'ㅋ', 'ㅌ', 'ㅍ', 'ㅎ' };
//// 중성 리스트. 00 ~20
//TCHAR JungsungList[] = { 
//	'ㅏ', 'ㅐ', 'ㅑ', 'ㅒ', 'ㅓ', 'ㅔ', 'ㅕ', 'ㅖ', 'ㅗ', 'ㅘ', 'ㅙ',
//	'ㅚ', 'ㅛ', 'ㅜ', 'ㅝ', 'ㅞ', 'ㅟ', 'ㅠ', 'ㅡ', 'ㅢ', 'ㅣ' };
////종성 리스트. 00 ~27 + 1(1개 없음)
//TCHAR JongsungList[] = {
//	' ', 'ㄱ', 'ㄲ', 'ㄳ', 'ㄴ', 'ㄵ', 'ㄶ', 'ㄷ', 'ㄹ', 'ㄺ', 'ㄻ',
//	'ㄼ', 'ㄽ', 'ㄾ', 'ㄿ', 'ㅀ', 'ㅁ', 'ㅂ', 'ㅄ', 'ㅅ', 'ㅆ', 'ㅇ',
//	'ㅈ', 'ㅊ', 'ㅋ', 'ㅌ', 'ㅍ', 'ㅎ' };

Font::Font()
{
	// 하드코딩 나가신다
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

			// 초중종성 분해
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
		// korean 자,모음
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
		// 아스키 + 한글 외에는 아무것도 그리지 않는다.
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
