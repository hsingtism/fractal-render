#include "fractal.h"
#include <stdio.h>
#include <complex.h>
#include <math.h>

int main() {
    // TODO set function, constant, and variable
    return 0;
}

void renderFrame(complex double topleft, complex double bottomright, int width, int height, int seqID) {
    unsigned char image[height][width][3];
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            //TODO iterate and generate colors here
            image[h][w][0] = 0;
            image[h][w][1] = 0;
            image[h][w][2] = 0;
        }
    }

    char filename[12];
    for (char exp = 7; exp > -1; exp--)
    {
        filename[exp] = (unsigned char)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = 0x2e;  // .
    filename[9] = 0x62;  // b
    filename[10] = 0x6d; // m
    filename[11] = 0x70; // p
    generateBitmapImage(image, height, width, filename);
    printf("%s rendered\n", filename);
}

void printComplex(complex double z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
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
