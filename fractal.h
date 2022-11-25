#include <stdint.h>
#include <complex.h>
#include <stdio.h>
#include <math.h>

#define PIXEL_FUNCTION 0 // like classic mandelbrot
#define PIXEL_SEED 1     // "julian"

#define IMAGE_SATURATION 1.0

#define BLUE 0
#define GREEN 1
#define RED 2

#define qNaNMask        0xFFFF000000000000

void printComplex(complex double z);

uint64_t getfpbits64(double x);
double setfpbits64(uint64_t x);

uint32_t getfpbits32(float x);
float setfpbits32(uint32_t x);
