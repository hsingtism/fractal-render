#include "fractal.h"
#include <stdlib.h>

/* self */         complex double iterator(complex double x, complex double c);
/* self */         void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration);
/* auxiliaryFunctions.c */uint32_t hsl2rgb(double h, double s, double l);
/* settings.c */   double iterate(complex double z, complex double c, int maxIteration);
/* settings.c */   complex double* colorTableData(complex double* table);
/* render.c */     void generateBitmapImage(unsigned char *image, int height, int width, char *fileName);

int main() {
    complex double colorTable[COLOR_TABLE_ALLOC_LENGTH * 2];
    

    renderFrame(
        -0.5 + 0.5 * I, // topleft
        0.5 + -0.5 * I, // bottomright
        0 + 0 * I,  // c
        PIXEL_SEED, //TODO move this to settings
        1920,        // TODO width and height doesn't work for larger images, fix this 
        1080,        // height
        2,          // filename
        1000        // TODO move this to settings
    );
    return 0;
}

/*
this giant function manages everything
renders and save an image
  - topleft - complex number of the image's top left
  - bottomright - complex numer of the image's bottom right 
  - secondParameter
  - mode whether to iterate
  - width - image width in pixels
  - height - image height in pixels
  - seqID - this will be stringified for the filename
  - maxIteration - the maximum amount of iteration for each pixel

*/
void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration) {
    // unsigned char image[height][width][3]; 
    // must be on heap to prevent stack overflow
    unsigned char * image = malloc(height * height * 3 * sizeof(unsigned char));

    complex double imagesize = bottomright - topleft;
    complex double pixelDeltaV = cimag(imagesize) / height;
    complex double pixelDeltaH = creal(imagesize) / width;
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            complex double position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            double pixel;
            if(mode) {
                pixel = iterate(position, secondParameter, maxIteration);
            } else {
                pixel = iterate(secondParameter, position, maxIteration);
            }
            //TODO iterate and generate colors here
            uint32_t color = 0;
            if(getfpbits(pixel) >> 63 == 0) {
                color = hsl2rgb(pixel, 0.1, 0.9);
            }
            image[3 * width * h + 3 * w + BLUE]  = color >> 8;
            image[3 * width * h + 3 * w + GREEN] = color >> 16;
            image[3 * width * h + 3 * w + RED]   = color >> 24;
        }
    }

    char filename[13];
    for (char exp = 7; exp > -1; exp--) { // base conversion
        filename[exp] = (unsigned char)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = (unsigned char)('.');
    filename[9] = (unsigned char)('b');
    filename[10] = (unsigned char)('m');
    filename[11] = (unsigned char)('p');
    filename[12] = (unsigned char)(0);
    generateBitmapImage((unsigned char *)image, height, width, filename);
    free(image);
    printf("%s rendered\n", filename);
}

double iterate(complex double z, complex double c, int maxIteration) {
    for (int i = 0; i < maxIteration; i++) {
        complex double zf = z;
        z = iterator(z, c);
        //TODO implement color table
        if(cabs(zf - 1.0) < 0.1) return 0.333;
        if(cabs(zf + 1.0) < 0.1) return 0.666;
        if(cabs(zf - (0.5842914495640625+1.174489106633826*I)) < 0.1) return 0.999;
    }
    return -0.1;
}
