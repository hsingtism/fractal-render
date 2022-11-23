#include "fractal.h"
#include <stdio.h>
#include <complex.h>
#include <math.h>

void renderFrame(complex double topleft, complex double bottomright, complex double c, int width, int height, int seqID, int maxIteration);
void printComplex(complex double z);
int iterate(complex double z, complex double c, int maxIteration);
complex double iterator(complex double x, complex double c);
complex double mandelbrot(complex double x, complex double c);
complex double polynomial(complex double x, complex double *coefficents, int degree);

int main() {
    // TODO set function, constant, and variable
    renderFrame(
        -2 + 2 * I, // topleft
        2 + -2 * I, // bottomright
        0 + 0 * I,  // c
        500,        // width
        500,        // height
        1,          // filename
        1000        // max iteration
    );
    return 0;
}

void renderFrame(complex double topleft, complex double bottomright, complex double c, int width, int height, int seqID, int maxIteration) {
    unsigned char image[height][width][3];
    complex double imagesize = bottomright - topleft;
    complex double pixelDeltaV = cimag(imagesize) / height;
    complex double pixelDeltaH = creal(imagesize) / width;
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            complex double position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            int pixel = iterate(c, position, maxIteration); //TODO depending on of z or c is changed, this needs to be switched
            //TODO iterate and generate colors here
            image[h][w][0] = pixel & 1 ? 0x7F : 0xFF;
            image[h][w][1] = pixel & 1 ? 0x7F : 0xFF;
            image[h][w][2] = pixel & 1 ? 0x7F : 0xFF;
        }
    }

    char filename[13];
    for (char exp = 7; exp > -1; exp--)
    {
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

void printComplex(complex double z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
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

/*
The pixel value is iterated here. Most elementary functions are supported.
If there is a more specific implementation, please use it because hardware is often more optimized for it.
For example, when taking a square root, use csqrt(x) instead of cpow(x, 0.5).

The following functions are widely supported. Check your complex.h support for it
 - mandelbrot(complex double z, complex double c) - make sure to include c
 - polynomial(complex x, complex double *coefficents, int degree) - optmized polynomial, 
    - x is value, 
    - *coefficients is array of coefficents, must be real, in reverse order of standard form
    - degree is the degree of the polynomial  
 - + add
 - - subtract
 - * multiply
 - / divide
 - cexp - natural exp
 - clog - natural log
 - cpow - general exp
 - csqrt - sqrt
 trig functions
 - csin - ccos - ctan
 inverse trig
 - casin - cacos - catan
 hyperbolic trig
 - csinh - ccosh - ctanh
 and its inverse
 - casinh - cacosh - catanh
*/
complex double iterator(complex double x, complex double c) {
    x = mandelbrot(x, c);
    return x;
}

complex double mandelbrot(complex double x, complex double c) {
    return x * x + c;
}

complex double polynomial(complex double x, complex double *coefficents, int degree) {
    complex double accumulator = coefficents[degree];
    for(; degree > 0; degree--) {
        accumulator = coefficents[degree] + accumulator * x;
    }
    return accumulator;
}
