#include "fractal.h"
#include <stdlib.h>
#include <string.h>

#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

/*
Generates and saves a bitmap image.
  - *image - ptr to array of 8 bit image data. byte image[HEIGHT][WIDTH][BYTES_PER_PIXEL]
      up to down > left ro right > blue, green, red
  - height of image. int
  - width of image. int
  - *filename - string of filename. char[]
*/
void generateBitmapImage(byte *image, int height, int width, char *fileName) {
    int widthInBytes = width * BYTES_PER_PIXEL;

    byte padding[3] = {0};
    int paddingSize = (4 - widthInBytes % 4) % 4;
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (widthInBytes + paddingSize) * height;

    byte * buffer = malloc(fileSize * sizeof(byte));

    int bufferPtr = 0; 

    // FILE HEADER
    byte fileHeader[FILE_HEADER_SIZE] = {0};

    fileHeader[0] = (byte)('B');
    fileHeader[1] = (byte)('M');
    fileHeader[2] = (byte)(fileSize);
    fileHeader[3] = (byte)(fileSize >> 8);
    fileHeader[4] = (byte)(fileSize >> 16);
    fileHeader[5] = (byte)(fileSize >> 24);
    fileHeader[10] = (byte)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
    memcpy(buffer + bufferPtr, fileHeader, FILE_HEADER_SIZE);
    bufferPtr += FILE_HEADER_SIZE;

    // INFO HEADER
    static byte infoHeader[INFO_HEADER_SIZE] = {0};

    infoHeader[0] = (byte)(INFO_HEADER_SIZE);
    infoHeader[4] = (byte)(width);
    infoHeader[5] = (byte)(width >> 8);
    infoHeader[6] = (byte)(width >> 16);
    infoHeader[7] = (byte)(width >> 24);
    infoHeader[8] = (byte)(height);
    infoHeader[9] = (byte)(height >> 8);
    infoHeader[10] = (byte)(height >> 16);
    infoHeader[11] = (byte)(height >> 24);
    infoHeader[12] = (byte)(1);
    infoHeader[14] = (byte)(BYTES_PER_PIXEL * 8);
    memcpy(buffer + bufferPtr, infoHeader, INFO_HEADER_SIZE);
    bufferPtr += INFO_HEADER_SIZE;

    for (int i = 0; i < height; i++) {
        memcpy(buffer + bufferPtr, image + i * widthInBytes, BYTES_PER_PIXEL * width);
        bufferPtr += BYTES_PER_PIXEL * width;
        memcpy(buffer + bufferPtr, padding, paddingSize);
        bufferPtr += paddingSize;
    }

    FILE *fp = fopen(fileName, "wb");
    fwrite(buffer, 1, fileSize, fp);
    fclose(fp);
    free(buffer);
}
