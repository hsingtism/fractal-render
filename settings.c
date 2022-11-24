#include "fractal.h"
#include <string.h>

// both from auxiliaryFunctions.c
complex double mandelbrot(complex double x, complex double c);
complex double polynomial(complex double x, complex double *coefficents, int degree);

/*
color table - tells how the pixel should be colored depending on where it end up
IT IS A 1D ARRAY, EACH ENTRY IS TWO ELEMENTS
structure
    - point - complex double - where the pixel end up, NaN payload for additional option
    These NaN payload should be in the real part. * indicates that tolerance needs to be set
        - paylmeaning
        0x0   approaches actual NaN
        0x1   
        0x2   absolute value approaches Infinity
        0x3  *absolute value greater than
        0x4  *absolute value less than
        0x5
        0x6  *diffabs from previous iteration (for attraction)
        0x7  *diffabs from initial value
        0x8  *orbit detection threshold
        0x9   
        0xA   iteration exceeds
        0xB   iteration exceeds - use voronoi on valid roots 
        0x7ffffffffffff (all ones)
    - tolerance and color - complex double double
        - tolerance - encoded in real part - how close it has to be to exit. or properties set by nan payload
        - color - encoded in imaginary part because color is imaginary - hue of color 0 to 1. infinity for white -infinity for black
*/
complex double* colorTableData(complex double* table) {
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    complex double tableDraft[COLOR_TABLE_ALLOC_LENGTH * 2] = {
        setfpbits(qNaNMask | APP_NAN)      + 0 * I, 0 - INFINITY * I,
        setfpbits(qNaNMask | ABS_APP_INF)  + 0 * I, 0 - INFINITY * I,
        setfpbits(qNaNMask | ABS_GRTR_THAN)+ 0 * I, 2 - INFINITY * I,
        setfpbits(qNaNMask | ITER_EXCEEDS) + 0 * I, 0 + INFINITY * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
        0 + 0 * I, 0 + 0 * I,
    };
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    memcpy(table, tableDraft, COLOR_TABLE_ALLOC_LENGTH * 2 * sizeof(complex double));
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
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    x = mandelbrot(x, c);
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    return x;
}
