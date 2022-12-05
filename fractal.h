#define PIXEL_FUNCTION 0 // like classic mandelbrot
#define PIXEL_SEED 1     // "julian"

#define ORBIT_DETECTION 0 // only useful for *very* deep iterations and/or very hard to iterate functions
#define ITERA_EQ_THRES pow(2, -16)
#define ORBIT_EQ_THRES pow(2, -32)

                             // a lower value (down to 1) may result in smoother colors for smoother coloring
#define ESCAPE_CHECK_FREQ 5  // but the program may take a performance hit. Higher values may result in excessive
                             // iterations. (~5 works the best for quadratic polynomials)

#define IMAGE_SATURATION 1.0
#define FP_INEXACT_WARNING_COEFFICENT 4.0

#include <stdint.h>
#include <complex.h>
#include <stdio.h>
#include <math.h>

#define BLUE 0
#define GREEN 1
#define RED 2

#define qNaNMask        0xFFFF000000000000

typedef unsigned char byte;
typedef complex double cplxdbl;

void printComplex(cplxdbl z);

uint64_t getfpbits64(double x);
double setfpbits64(uint64_t x);

uint32_t getfpbits32(float x);
float setfpbits32(uint32_t x);
