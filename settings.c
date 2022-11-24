#include "fractal.h"
#include <string.h>

complex double mandelbrot(complex double x, complex double c);
complex double polynomial(complex double x, complex double *coefficents, int degree);
void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration);

/* DEFINES WHAT TO DO WHEN PROGRAM IS STARTED*/
// TODO consider moving main to here
void action() {
    renderFrame(
        /* topleft */     -0.5 + 0.5 * I,
        /* bottomright */ 0.5 + -0.5 * I,
        /* constant */    0 + 0 * I,  // optional depending on how the iterator is set up
        /* iterated val*/ PIXEL_SEED,
        /* image width */ 1080,
        /* image height */1080,
        /* file name*/    2,
        /* max iteration*/1000
    );
}

/*
CAREFUL: 0.0 AND -0.0 IS RESERVED FOR "CONTINUE", TO ESCAPE WITH COLOR, USE 1.0

z - current iteration value
previous - previous iteration value
initial - initial iteration value
TODO implement orbit detection

return value means the following
  - any zero - continue iterating
  - any negative (excl. -0.0, incl. negative infinity and negative nan) - black
  - real number (0, 1] hue of color. 0 being blue
  - positive nan
   TODO implement nan payload here
*/
double escapeManager(complex double z, complex double previous, complex double initial, complex double c) {
    if(cabs(z - 1.0) < 0.1) return 0.333;
    if(cabs(z + 1.0) < 0.1) return 0.666;
    if(cabs(z - (0.5842914495640625+1.174489106633826*I)) < 0.1) return 0.999;
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

 TODO make newton fractals more easy to define
*/
complex double iterator(complex double x, complex double c) {
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    // x = mandelbrot(x, c);
    x -= ((x * x - 1) * (x - (0.5842914495640625+1.174489106633826*I)))
         / (2 * x * (x - (0.5842914495640625+1.174489106633826*I)) + (x * x - 1));
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    return x;
}
