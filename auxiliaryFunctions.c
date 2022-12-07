#include "fractal.h"

// use only for debug
void printComplex(cplxdbl z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
}

void floatingPointPercisionWarn(cplxdbl topleft, cplxdbl bottomright, double pixelDeltaV, double pixelDeltaH) {
    double fpdelta_real = fmax( // in case the frame crosses exponents
            fabs(creal(topleft) - setfpbits64(getfpbits64(creal(topleft)) ^ 0x1)),
            fabs(creal(bottomright) - setfpbits64(getfpbits64(creal(bottomright)) ^ 0x1))
        );
    double fpdelta_imag = fmax(
            fabs(cimag(topleft) - setfpbits64(getfpbits64(cimag(topleft)) ^ 0x1)),
            fabs(cimag(bottomright) - setfpbits64(getfpbits64(cimag(bottomright)) ^ 0x1))
        );

    if(fpdelta_imag * FP_INEXACT_WARNING_COEFFICENT >= fabs(pixelDeltaV)) {
        printf("potential floating point impercision. imag-axis avg r/p %f\n", fabs(pixelDeltaV) / fpdelta_imag);
    }
    if(fpdelta_real * FP_INEXACT_WARNING_COEFFICENT >= fabs(pixelDeltaH)) {
        printf("potential floating point impercision. real-axis avg r/p %f\n", fabs(pixelDeltaH) / fpdelta_real);
    }
}

void writeFileName(char* dest, int seqID) {
    for (char exp = 7; exp > -1; exp--) { // base conversion
        dest[exp] = (byte)(48 + seqID % 10);
        seqID /= 10;
    }
    dest[8] = (byte)'.';
    dest[9] = (byte)'b';
    dest[10] = (byte)'m';
    dest[11] = (byte)'p';
    dest[12] = (byte)0;
}

// floating point <-> its bit representation
uint64_t getfpbits64(double x) { return * ( uint64_t * ) &x; }
double setfpbits64(uint64_t x) { return * ( double * ) &x; }
uint32_t getfpbits32(float x) { return * ( uint32_t * ) &x; }
float setfpbits32(uint32_t x) { return * ( float * ) &x; }

cplxdbl mandelbrot(cplxdbl x, cplxdbl c) {
    return x * x + c;
}

cplxdbl mean(cplxdbl *val, int length) {
    for(int i = 1; i < length; i++) { // using val[0] as accumlator
        val[0] += val[i];
    }
    return val[0] / length;
}

// polynomial eval with horners method
// accumlator is used for internal recusion, set to 0
cplxdbl polynomialCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator) {
    if (degree == 0) return accumlator;
    return polynomialCoeff(x, coefficents, degree - 1, coefficents[degree - 1] + accumlator * x);
}

// polynomial eval with roots (fundemental thorem)
// scaling is used for internal recursion, set to 1 if there is no constant factor
cplxdbl polynomialRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling) {
    if (degree == 0) return scaling;
    return polynomialRoots(x, roots, degree - 1, scaling * (x - roots[degree - 1]));
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

// calling cabs after each iteration is very wasteful, this can be used instead
double maxAxis(cplxdbl x) {
    return fmax(fabs(creal(x)), fabs(cimag(x)));
}
