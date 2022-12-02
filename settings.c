#include "fractal.h"

cplxdbl mandelbrot(cplxdbl x, cplxdbl c);
cplxdbl polynomialCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator);
cplxdbl polynomialRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling);
cplxdbl mean(cplxdbl *val, int length);
void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl secondParameter, byte mode, int width, int height, int seqID, int maxIteration);

// TODO derviative calculation for newtons method
// TODO auto zoom based on detail leavel

/* DEFINES WHAT TO DO WHEN PROGRAM IS STARTED */
int main() {

    /* ---------------- EDIT BELOW THIS LINE ---------------- */

    renderFrame(
        /* topleft */     -2 + 2 * I,
        /* bottomright */ 2 - 2 * I,
        /* constant */    0 + 0 * I,  // optional depending on how the iterator is set up
        /* iterated val*/ PIXEL_FUNCTION, // PIXEL_SEED maps pixel to "z", PIXEL_FUNCTION maps pixel to "c"
        /* image width */ 1920,
        /* image height */1080,
        /* file name*/    3,
        /* max iteration*/1000
    );
    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return 0;
}

/*
  - z - current iteration value
  - previous - previous iteration value
  - initial - initial iteration value
  - i - number of iterations (for coloring)
TODO implement orbit detection (maybe)

return value means the following
  - all zero - continue iterating
  - 2 single percision floats encoded into a 64 bit uint. 
    32 msb for lightness and 32 lsb for hue, both [0, 1] 
  - for black, set hue to something non-zero to make it truthy
*/
uint64_t escapeManager(cplxdbl z, cplxdbl previous, cplxdbl c, int i) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */

    // if(cabs(z - 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.3333);
    // if(cabs(z + 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.6666);
    // if(cabs(z - (0.5842914495640625+1.174489106633826*I)) < 0.1) return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.9999);
    if(cabs(z) > 2) return ((uint64_t)getfpbits32(powf((float)i / 1000.0f, 30.0f)) << 32) | getfpbits32(powf((float)i / 1000.0f, 5.0f) + 0.1); // TODO do not add 0.1 like this, implement something to normalize it
    if(cabs(previous - z) < 0.00001) return ((uint64_t)getfpbits32(0.0) << 32) | getfpbits32(0.1);
    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return 0;
}

/*
The pixel value is iterated here. 
All basic operations ( + - * / ) and functions supported by complex.h is avilable here

Additionally, the following functions are intended to be used in here

cplxdbl mean(cplxdbl *val, int length);
  - calculates the mean of array

cplxdbl mandelbrot(cplxdbl x, cplxdbl c);
  - iterate with the mandelbrot set function 
cplxdbl polynomialCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator);
  - evaluate polynomials with a list of coefficents (horners method)
cplxdbl polynomialRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling);
  - evaluate polynomials with a list of roots (simple x - root method)
  - x is value
  - *coefficents or *roots is an array of coefficents and roots
  - *coefficents must be in reverse standard form c[d] is the coefficent of x^d
  - degree is the degree of the polynomial
  - accumlator should be 0 
  - scaling should be 1 (or the factored out constant)

 TODO make newton fractals more easy to define d/dx of factored polynomials
*/
cplxdbl iterator(cplxdbl x, cplxdbl c) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    
    x = mandelbrot(x, c);
    // (x - (0.5842914495640625+1.174489106633826*I)))

    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return x;
}
