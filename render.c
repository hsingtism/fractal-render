#include "fractal.h"

#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

/*
Generates and saves a bitmap image.
  - *image - ptr to array of 8 bit image data. unsigned char image[HEIGHT][WIDTH][BYTES_PER_PIXEL]
      up to down > left ro right > blue, green, red
  - height of image. int
  - width of image. int
  - *filename - string of filename. char[]
*/
void generateBitmapImage(unsigned char *image, int height, int width, char *fileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0};
    int paddingSize = (4 - widthInBytes % 4) % 4;

    FILE *fp = fopen(fileName, "wb");
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (widthInBytes + paddingSize) * height;

    // FILE HEADER
    unsigned char fileHeader[FILE_HEADER_SIZE] = {0};

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, fp);

    // INFO HEADER
    static unsigned char infoHeader[INFO_HEADER_SIZE] = {0};

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, fp);

    for (int i = 0; i < height; i++)
    {
        fwrite(image + i * widthInBytes, BYTES_PER_PIXEL, width, fp);
        fwrite(padding, 1, paddingSize, fp);
    }

    fclose(fp);
}
