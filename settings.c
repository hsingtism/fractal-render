#include "fractal.h"

/*
color table - tells how the pixel should be colored depending on where it end up
IT IS A 1D ARRAY, EACH ENTRY IS TWO ELEMENTS
structure
    - point - complex double - where the pixel end up, NaN payload for additional option
    These NaN payload should be in the real part. * indicates that tolerance needs to be set
        - paylmeaning
        0   approaches actual NaN
        1   
        2   absolute value approaches Infinity
        3  *absolute value greater than
        4  *absolute value less than
        5
        6  *diffabs from previous iteration (for attraction)
        7  *diffabs from initial value
        8  *orbit detection threshold
        9   
        A   iteration exceeds
        B   iteration exceeds - use voronoi on valid roots 
    - tolerance and color - complex double double
        - tolerance - encoded in real part - how close it has to be to exit. or properties set by nan payload
        - color - encoded in imaginary part because color is imaginary - hue of color 0 to 1. infinity for white -infinity for black
*/
complex double* colorTable() {
    complex double table[2] = {};
    return table;
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
    for(degree--; degree > -1; degree--) {
        accumulator = coefficents[degree] + accumulator * x;
    }
    return accumulator;
}