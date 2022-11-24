#include "fractal.h"

// use only for debug
void printComplex(complex double z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
}

inline uint64_t getfpbits(double x) {
    return * ( uint64_t * ) &x;
}

inline double setfpbits(uint64_t x) {
    return * ( double * ) &x;
}

void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration);
int iterate(complex double z, complex double c, int maxIteration);
uint32_t hsl2rgb(double h, double s, double l);
complex double iterator(complex double x, complex double c);
complex double mandelbrot(complex double x, complex double c);
complex double polynomial(complex double x, complex double *coefficents, int degree);

int main() {
    // TODO set function, constant, and variable
    // TODO user specified color table
    renderFrame(
        -2 + 2 * I, // topleft
        2 + -2 * I, // bottomright
        0 + 0 * I,  // c
        PIXEL_FUNCTION, //TODO this argument will be removed, it is here for testing
        500,        // width
        500,        // height
        1,          // filename
        1000        // max iteration
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
    unsigned char image[height][width][3];
    complex double imagesize = bottomright - topleft;
    complex double pixelDeltaV = cimag(imagesize) / height;
    complex double pixelDeltaH = creal(imagesize) / width;
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            complex double position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            int pixel;
            if(mode) {
                pixel = iterate(position, secondParameter, maxIteration);
            } else {
                pixel = iterate(secondParameter, position, maxIteration);
            }
            //TODO iterate and generate colors here
            uint32_t color = hsl2rgb(0, 0, (double)pixel);
            image[h][w][BLUE]  = color >> 8;
            image[h][w][GREEN] = color >> 16;
            image[h][w][RED]   = color >> 24;
        }
    }

    char filename[13];
    for (char exp = 7; exp > -1; exp--) { // base conversion
        filename[exp] = (unsigned char)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = 0x2e;  // .
    filename[9] = 0x62;  // b
    filename[10] = 0x6d; // m
    filename[11] = 0x70; // p
    filename[12] = 0x00; // null
    generateBitmapImage((unsigned char *)image, height, width, filename);
    printf("%s rendered\n", filename);
}

int iterate(complex double z, complex double c, int maxIteration) {
    for (int i = 0; i < maxIteration; i++) {
        complex double zf = z;
        z = iterator(z, c);
        //TODO let this be customizable
        if(cabs(z) > 1000) return 1;
        if(cabs(zf - z) < 0.00001 && i > 0) return 0;
    }
    return 0;
}
