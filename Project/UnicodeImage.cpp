#include "UnicodeImage.h"

const char map[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";// " .:-=+*#%@"; //" .,:;ox%#@";

UnicodeImage::UnicodeImage(const char* filename, int width, int height)
	:width(width)
	,height(height)
	,image(NULL)
{
    /*
    * VARIABLES ---------------------
    * Creation of two instances of images of unsigned char pixels.
    * The first image _image_ is initialized by reading an image file from the disk.
    * Here, lena.jpg must be in the same directory than the current program.
    * Note that you must also have installed the ImageMagick package
    * in order to be able to read JPG images.
    * var(size_x, size_y, size_z, dv, default_fill)
    */
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

	this->image = new char[width * height];
    this->mask = new bool[width * height];
    
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
            unsigned char v = grayWeight(w, h, 0, 0);

            this->image[h * width + w] = map[(v) * 70 / 256];
            this->mask[h * width + w] = mask(w, h, 0, 0) == 1;
		}
	}
}

UnicodeImage::~UnicodeImage()
{
	delete[] this->image;
	this->image = NULL;
}

void UnicodeImage::DrawTo(RenderBuffer* buffer, const POINT& pos)
{
    RenderBuffer::ImageData data;
    data.image = image;
    data.mask = mask;
    data.imageWidth = this->width;
    data.imageHeight = this->height;

    buffer->Draw(data, pos);
}

void UnicodeImage::DrawTo(RenderBuffer* buffer, const POINT& pos, const RECT& imageRect)
{
    RenderBuffer::ImageData data;
    data.image = image;
    data.mask = mask;
    data.imageWidth = this->width;
    data.imageHeight = this->height;

    buffer->Draw(data, pos, imageRect);
}

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
