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

complex double mandelbrot(complex double x, complex double c) {
    return x * x + c;
}

// polynomial eval with horners method
complex double polynomial(complex double x, complex double *coefficents, int degree) {
    complex double accumulator = coefficents[degree];
    for(degree--; degree > -1; degree--) {
        accumulator = coefficents[degree] + accumulator * x;
    }
    return accumulator;
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
