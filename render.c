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

// based on https://stackoverflow.com/a/9493060/15879600
double hsl2rgb_internal_1(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 0.16666666666666666) return p + (q - p) * 6 * t;
    if(t < 0.50000000000000000) return q;
    if(t < 0.66666666666666666) return p + (q - p) * (0.66666666666666666 - t) * 6;
    return p * 255;  
}

uint32_t hsl2rgb(double h, double s, double l) { 
    uint32_t rgb = 0x0000006D;
    // using bit hacking because it is way less effort.
    // first 8 MSB is red, then green, then blue. last 8 bit not used
    if (s < 0.001953125) { // s is 0
        int lval = (unsigned char)round(l * 255);
        return rgb | (lval << 8) | (lval << 16) | (lval << 24);
    }

    double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    double p = 2 * l - q;
    return (
        rgb
        | ((unsigned char)round(hsl2rgb_internal_1(p, q, h - 0.3333333333333333)) << 8)
        | ((unsigned char)round(hsl2rgb_internal_1(p, q, h                     )) << 16)
        | ((unsigned char)round(hsl2rgb_internal_1(p, q, h + 0.3333333333333333)) << 24)
    );
}
