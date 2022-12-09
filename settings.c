#include "fractal.h"

double maxAxis(cplxdbl x);
void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl secondParameter, byte mode, int width, int height, int seqID, int maxIteration);

#define CENTER 0.3602404434377639253623 - 0.6413130610647825040291 * I
#define Z_SPEED_R 1
#define Z_SPEED_I 1
int maxIter_GLOBAL = 0;
#include "defineI.h"

/* DEFINES WHAT TO DO WHEN PROGRAM IS STARTED */
int main() {

    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    int i = cmdfeedI - 4;
    // for(int i = 8; i < 20; i++) {
        maxIter_GLOBAL = (int)exp((double)i / 5 + 9); // TODO a way to detect this
        printf("%d\n", maxIter_GLOBAL);
        renderFrame(
            /* topleft */     CENTER - cexp(-i * Z_SPEED_R) + cexp(-i * Z_SPEED_I) * I,//-2 + 2 * I,
            /* bottomright */ CENTER + cexp(-i * Z_SPEED_R) - cexp(-i * Z_SPEED_I) * I,//2 - 2 * I,
            /* constant */    0 + 0 * I,  // optional depending on how the iterator is set up
            /* iterated val*/ PIXEL_FUNCTION, // PIXEL_SEED maps pixel to "z", PIXEL_FUNCTION maps pixel to "c"
            /* image width */ 1000,
            /* image height */1000,
            /* file name*/    i + 16,
            /* max iteration*/maxIter_GLOBAL
        );
    // }
    
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
    if (getfpbits64(creal(previous)) == getfpbits64(NAN)) return 0;
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */

    // if(cabs(z - 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.3333);
    // if(cabs(z + 1.0) < 0.1)                                      return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.6666);
    // if(cabs(z - (0.5842914495640625+1.174489106633826*I)) < 0.1) return ((uint64_t)getfpbits32(1.0) << 32) | getfpbits32(0.9999);
    if(maxAxis(z) > 2) return ((uint64_t)getfpbits32(powf((float)i / (float)maxIter_GLOBAL, 50.0f * powf(1.1, cmdfeedI))) << 32) | getfpbits32(powf((float)i / (float)maxIter_GLOBAL, 5.0f));
    if(maxAxis(previous - z) < ITERA_EQ_THRES) return ((uint64_t)getfpbits32(0.0) << 32) | getfpbits32(0.1);
    if(ORBIT_DETECTION && maxAxis(orbit - z) < ORBIT_EQ_THRES) return ((uint64_t)getfpbits32(0.0) << 32) | getfpbits32(0.1);
    
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

//  evaluate the derviative of a polynomial  
cplxdbl polyDerivRoots(cplxdbl x, cplxdbl *roots, int degree, cplxdbl scaling);
cplxdbl polyDerivCoeff(cplxdbl x, cplxdbl *coefficents, int degree, cplxdbl accumlator);

//  iterate via newton's method
cplxdbl newtonRoots(cplxdbl x, cplxdbl *roots, int degree);
cplxdbl newtonCoeff(cplxdbl x, cplxdbl *coefficents, int degree);

//  calculates the mean of array
cplxdbl mean(cplxdbl *val, int length);

cplxdbl iterator(cplxdbl x, cplxdbl c) {
    
    /* ---------------- EDIT BELOW THIS LINE ---------------- */
    
    x = mandelbrot(x, c);
    // (x - (0.5842914495640625+1.174489106633826*I)))

    
    /* ---------------- EDIT ABOVE THIS LINE ---------------- */
    
    return x;
}
