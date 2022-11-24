#include <stdint.h>
#include <complex.h>
#include <stdio.h>
#include <math.h>

#define PIXEL_FUNCTION 0 // like classic mandelbrot
#define PIXEL_SEED 1     // "julian"

#define BLUE 0
#define GREEN 1
#define RED 2

#define COLOR_TABLE_ALLOC_LENGTH 16

#define qNaNMask        0xFFFF000000000000

void printComplex(complex double z);
uint64_t getfpbits(double x);
double setfpbits(uint64_t x);
