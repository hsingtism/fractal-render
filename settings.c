#include "fractal.h"

double maxAxis(cplxdbl x);
void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl secondParameter, byte mode, int width, int height, int seqID, int maxIteration);

//TODO auto color management for newton
//TODO escape tempate for mandelbrot
//TODO template for zoom

/* DEFINES WHAT TO DO WHEN PROGRAM IS STARTED */
int main() {

    /* ---------------- EDIT BELOW THIS LINE ---------------- */

        renderFrame(
            /* topleft */     -2 + 2 * I,
            /* bottomright */ 2 - 2 * I,
            /* constant */    0 + 0 * I,  // optional depending on how the iterator is set up
            /* iterated val*/ PIXEL_SEED, // PIXEL_SEED maps pixel to "z", PIXEL_FUNCTION maps pixel to "c"
            /* image width */ 1000,
            /* image height */1000,
            /* file name*/    7,
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

return value means the following
  - all zero - continue iterating
  - 2 single percision floats encoded into a 64 bit uint. 
    32 msb for lightness and 32 lsb for hue, both [0, 1] 
  - for black, set hue to something non-zero to make it truthy

NOTE: performance of this function is very important. this function may be called as often as the iterator
double maxAxis(cplxdbl x) can be used in place of cabs to prevent excessive hypot calls
*/
uint64_t escapeManager(cplxdbl z, cplxdbl previous, cplxdbl c, int i, cplxdbl orbit) {
    if (isnan(creal(z))) return 0x1; // returns if NAN
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */

    if(maxAxis(z - 1.0) < ITERA_EQ_THRES)                                      return ((uint64_t)getfpbits32(0.5f) << 32) | getfpbits32(0.3333f);
    if(maxAxis(z + 1.0) < ITERA_EQ_THRES)                                      return ((uint64_t)getfpbits32(0.5f) << 32) | getfpbits32(0.6666f);
    if(maxAxis(z - (0.5842914495640625+1.174489106633826*I)) < ITERA_EQ_THRES) return ((uint64_t)getfpbits32(0.5f) << 32) | getfpbits32(0.9999f);

    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return 0;
}

/*
The pixel value is iterated here. 
All basic operations ( + - * / ) and functions supported by complex.h is avilable here

Additionally, the following functions are intended to be used in here */
//  iterate with the mandelbrot set function
cplxdbl mandelbrot(cplxdbl x, cplxdbl c);

//  evaluate polynomial with coefficents
cplxdbl polynomialCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator);

//  evaluate polynomial with roots
cplxdbl polynomialRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling);

// TODO these don't work
//  evaluate the derviative of a polynomial  
// cplxdbl polyDerivRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling);
// cplxdbl polyDerivCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator);
//  iterate via newton's method
// cplxdbl newtonRoots(cplxdbl x, cplxdbl *roots, int degree);
// cplxdbl newtonCoeff(cplxdbl x, cplxdbl *coefficents, int degree);

//  calculates the mean of array
cplxdbl mean(cplxdbl *val, int length);

cplxdbl iterator(cplxdbl x, cplxdbl c) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    
    // x = mandelbrot(x, c);
    cplxdbl roots[3] = {-1, 1, 0.5842914495640625+1.174489106633826*I};
    // x -= ((x * x - 1) * (x - (0.5842914495640625+1.174489106633826*I)))
    //      / (2 * x * (x - (0.5842914495640625+1.174489106633826*I)) + (x * x - 1));
    x -= polynomialRoots(x, roots, 3, 1)
         / (2 * x * (x - (0.5842914495640625+1.174489106633826*I)) + (x * x - 1));

    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return x;
}
