#include "Image.h"

const TCHAR map[] = TEXT(" .,:;ox%#@"); //" .,:;ox%#@";
int mapSize = 10;
int contrastcurve[] = { 0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,6,7,8,8,9,9,10,10,11,12,12,13,14,14,15,16,17,17,18,19,20,21,22,23,23,24,25,26,27,28,29,30,31,32,33,34,35,37,38,39,40,41,42,43,45,46,47,48,49,51,52,53,54,56,57,58,60,61,62,64,65,66,68,69,71,72,73,75,76,78,79,81,82,84,85,87,88,90,91,93,94,96,97,99,100,102,103,105,106,108,109,111,113,114,116,117,119,120,122,124,125,127,128,130,131,133,135,136,138,139,141,142,144,146,147,149,150,152,153,155,156,158,159,161,162,164,165,167,168,170,171,173,174,176,177,179,180,182,183,184,186,187,189,190,191,193,194,195,197,198,199,201,202,203,204,206,207,208,209,210,212,213,214,215,216,217,218,220,221,222,223,224,225,226,227,228,229,230,231,232,232,233,234,235,236,237,238,238,239,240,241,241,242,243,243,244,245,245,246,246,247,247,248,249,249,249,250,250,251,251,252,252,252,253,253,253,253,254,254,254,254,254,255,255,255,255,255,255,255,255 };

Image::Image() 
    : image(NULL)
    , mask(NULL)
    , width(0)
    , height(0)
{
}

Image::Image(TCHAR* image, bool* mask, int width, int height)
    : image(image)
    , mask(mask)
    , width(width)
    , height(height)
{
}

Image::~Image()
{
	delete[] this->image;
    delete[] this->mask;
}

Image* Image::LoadBmp(const char* filename)
{
    CImg<int> temp(filename);
    
    int width = temp.width();
    int height = temp.height();

    CImg<int> grayWeight(width, height, 1, 1, 0),
        imgR(width, height, 1, 3, 0),
        imgG(width, height, 1, 3, 0),
        imgB(width, height, 1, 3, 0);

    CImg<int> mask(width, height, 1, 1, 0);

    // for all pixels x,y in image
    cimg_forXY(temp, x, y) {
        imgR(x, y, 0, 0) = temp(x, y, 0, 0),    // Red component of image sent to imgR
        imgG(x, y, 0, 1) = temp(x, y, 0, 1),    // Green component of image sent to imgG
        imgB(x, y, 0, 2) = temp(x, y, 0, 2);    // Blue component of image sent to imgB

        // Separation of channels
        int R = (int)temp(x, y, 0, 0);
        int G = (int)temp(x, y, 0, 1);
        int B = (int)temp(x, y, 0, 2);

        // Real weighted addition of channels for gray
        int grayValueWeight = (int)(0.299 * R + 0.587 * G + 0.114 * B);

        // saving píxel values into image information
        grayWeight(x, y, 0, 0) = grayValueWeight;
        mask(x, y, 0, 0) = (R == 255 && G == 0 && B == 255) ? 0 : 1;
    }

    TCHAR *image = new TCHAR[width * height];
    bool *m = new bool[width * height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            unsigned char v = grayWeight(w, h, 0, 0);

            image[h * width + w] = map[(v) *mapSize / 256];
            m[h * width + w] = mask(w, h, 0, 0) == 1;
        }
    }
    return new Image(image, m, width, height);
}

Image* Image::LoadBmp(const char* filename, int width, int height)
{
    CImg<int> temp(filename),
        grayWeight(width, height, 1, 1, 0),
        imgR(width, height, 1, 3, 0),
        imgG(width, height, 1, 3, 0),
        imgB(width, height, 1, 3, 0);

    CImg<int> mask(width, height, 1, 1, 0);

    temp.resize(width, height);

    // for all pixels x,y in image
    cimg_forXY(temp, x, y) {
        imgR(x, y, 0, 0) = temp(x, y, 0, 0),    // Red component of image sent to imgR
        imgG(x, y, 0, 1) = temp(x, y, 0, 1),    // Green component of image sent to imgG
        imgB(x, y, 0, 2) = temp(x, y, 0, 2);    // Blue component of image sent to imgB

        // Separation of channels
        int R = (int)temp(x, y, 0, 0);
        int G = (int)temp(x, y, 0, 1);
        int B = (int)temp(x, y, 0, 2);

        // Real weighted addition of channels for gray
        int grayValueWeight = (int)(0.299 * R + 0.587 * G + 0.114 * B);

        // saving píxel values into image information
        grayWeight(x, y, 0, 0) = grayValueWeight;
        mask(x, y, 0, 0) = (R == 255 && G == 0 && B == 255) ? 0 : 1;
    }

	TCHAR* image = new TCHAR[width * height];
    bool* m = new bool[width * height];
    
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
            unsigned char v = grayWeight(w, h, 0, 0);

            image[h * width + w] = map[(v) * mapSize / 256];
            m[h * width + w] = mask(w, h, 0, 0) == 1;
		}
	}
    return new Image(image, m, width, height);
}

Image* Image::FromText(const char* text, int width, int height)
{
    return new Image();
}

//void Image::DrawTo(RenderBuffer* buffer, const POINT& pos)
//{
//    RenderBuffer::ImageData data;
//    data.image = image;
//    data.mask = mask;
//    data.imageWidth = this->width;
//    data.imageHeight = this->height;
//
//    buffer->Draw(data, pos);
//}
//
//void Image::DrawTo(RenderBuffer* buffer, const POINT& pos, const RECT& imageRect)
//{
//    RenderBuffer::ImageData data;
//    data.image = image;
//    data.mask = mask;
//    data.imageWidth = this->width;
//    data.imageHeight = this->height;
//
//    buffer->Draw(data, pos, imageRect);
//}

//UnicodeSprite::UnicodeSprite(const char* const filename, int width, int height, int col, int row) 
//    : UnicodeImage(filename, width, height)
//{
//    this->col = col;
//    this->row = row;
//
//    this->cellWidth = floor(width / col);
//    this->cellHeight = floor(height / row);
//}
//
//void UnicodeSprite::DrawTo(RenderBuffer* buffer, const POINT& pos, int colNum, int rowNum)
//{
//    RECT rect = {
//        colNum * this->cellWidth,
//        rowNum * this->cellHeight,
//        (colNum + 1) * this->cellWidth,
//        (rowNum + 1) * this->cellHeight
//    };
//
//    UnicodeImage::DrawTo(buffer, pos, rect);
//}
