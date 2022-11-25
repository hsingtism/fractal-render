#include "fractal.h"
#include <string.h>

cplxdbl mandelbrot(cplxdbl x, cplxdbl c);
cplxdbl polynomial(cplxdbl x, cplxdbl *coefficents, int degree);
void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl secondParameter, byte mode, int width, int height, int seqID, int maxIteration);

/* DEFINES WHAT TO DO WHEN PROGRAM IS STARTED*/
// TODO consider moving main to here
int main() {

    /* ---------------- EDIT BELOW THIS LINE ---------------- */

    renderFrame(
        /* topleft */     -0.5 + 0.5 * I,
        /* bottomright */ 0.5 + -0.5 * I,
        /* constant */    0 + 0 * I,  // optional depending on how the iterator is set up
        /* iterated val*/ PIXEL_SEED, // PIXEL_SEED maps pixel to "z", PIXEL_FUNCTION maps pixel to "c"
        /* image width */ 1080,
        /* image height */1080,
        /* file name*/    2,
        /* max iteration*/1000
    );
    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return 0;
}

/*
z - current iteration value
previous - previous iteration value
initial - initial iteration value
i - number of iterations (for colorinf)
TODO implement orbit detection

return value means the following
  - all zero - continue iterating
  - 2 single percision floats encoded into a 64 bit uint. 
    32 msb for lightness and 32 lsb for hue, both [0, 1] 
  - for black, set hue to something non-zero to make it truthy
*/
uint64_t escapeManager(cplxdbl z, cplxdbl previous, cplxdbl c, int i) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    
    if(cabs(z - 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.3333);
    if(cabs(z + 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.6666);
    if(cabs(z - (0.5842914495640625+1.174489106633826*I)) < 0.1) return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.9999);
    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return 0;
}

/*
The pixel value is iterated here. Most elementary functions are supported.
If there is a more specific implementation, please use it because hardware is often more optimized for it.
For example, when taking a square root, use csqrt(x) instead of cpow(x, 0.5).

The following functions are widely supported. Check your complex.h support for it
 - mandelbrot(cplxdbl z, cplxdbl c) - make sure to include c
 - polynomial(complex x, cplxdbl *coefficents, int degree) - optmized polynomial, 
    - x is value, 
    - *coefficients is array of coefficents, must be real, in reverse order of standard form
    - degree is the degree of the polynomial  
 - + add               - - subtract
 - * multiply          - / divide
 - cexp - natural exp  - clog - natural log
 - cpow - general exp  - csqrt - sqrt
 - csin                - ccos                - ctan (trig and inverse)
 - casin               - cacos               - catan
 - csinh               - ccosh               - ctanh (hyperbolic)
 - casinh              - cacosh              - catanh

 TODO make newton fractals more easy to define
*/
cplxdbl iterator(cplxdbl x, cplxdbl c) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    
    // x = mandelbrot(x, c);
    x -= ((x * x - 1) * (x - (0.5842914495640625+1.174489106633826*I)))
         / (2 * x * (x - (0.5842914495640625+1.174489106633826*I)) + (x * x - 1));
    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return x;
}
