#include "fractal.h"

// use only for debug
void printComplex(cplxdbl z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
}

// floating point <-> its bit representation
uint64_t getfpbits64(double x) { return * ( uint64_t * ) &x; }
double setfpbits64(uint64_t x) { return * ( double * ) &x; }
uint32_t getfpbits32(float x) { return * ( uint32_t * ) &x; }
float setfpbits32(uint32_t x) { return * ( float * ) &x; }

cplxdbl mandelbrot(cplxdbl x, cplxdbl c) {
    return x * x + c;
}

// polynomial eval with horners method
cplxdbl polynomialCoeff(cplxdbl x, cplxdbl *coefficents, int degree) {
    cplxdbl accumulator = coefficents[degree];
    for(degree--; degree > -1; degree--) {
        accumulator = coefficents[degree] + accumulator * x;
    }
    return accumulator;
}

// polynomial eval with roots (fundemental thorem)
cplxdbl polynomialRoots(cplxdbl x, cplxdbl *roots, int degree) {
    cplxdbl accumlator = 1;
    for(degree--; degree > -1; degree--) {
        accumlator *= x - roots[degree];
    }
    return accumlator;
}

// based on https://stackoverflow.com/a/9493060/15879600
double hsl2rgb_internal_1(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 0.16666666666666666) return p + (q - p) * 6 * t;
    if(t < 0.50000000000000000) return q;
    if(t < 0.66666666666666666) return p + (q - p) * (0.66666666666666666 - t) * 6;
    return p;  
}

uint32_t hsl2rgb(double h, double s, double l) { 
    uint32_t rgb = 0x0000006D;
    // using bit hacking because it is way less effort.
    // first 8 MSB is red, then green, then blue. last 8 bit not used
    if (s < 0.001953125) { // s is 0
        int lval = (byte)round(l * 255);
        return rgb | (lval << 8) | (lval << 16) | (lval << 24);
    }

    double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    double p = 2 * l - q;
    return (
        rgb
        | ((byte)round(hsl2rgb_internal_1(p, q, h - 0.3333333333333333) * 255) << 8)
        | ((byte)round(hsl2rgb_internal_1(p, q, h                     ) * 255) << 16)
        | ((byte)round(hsl2rgb_internal_1(p, q, h + 0.3333333333333333) * 255) << 24)
    );
}
