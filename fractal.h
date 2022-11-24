#include <stdint.h>
#include <complex.h>
#include <stdio.h>
#include <math.h>

#define PIXEL_FUNCTION 0 // like classic mandelbrot
#define PIXEL_SEED 1     // "julian"

#define BLUE 0
#define GREEN 1
#define RED 2

#define qNaNMask        0xFFFF000000000000

#define APP_NAN         0x0000000000000000
#define ABS_APP_INF     0x0000000000000002
#define ABS_GRTR_THAN   0x0000000000000003
#define ABS_LESS_THAN   0x0000000000000004
#define DIFFABS_PREV    0x0000000000000006
#define DIFFABS_INIT    0x0000000000000007
#define ORBIT_DETECT    0x0000000000000008
#define ITER_EXCEEDS    0x000000000000000A
#define USE_VORONOI     0x000000000000000B

void generateBitmapImage(unsigned char *image, int height, int width, char *fileName);
uint32_t hsl2rgb(double h, double s, double l);
complex double* colorTable();
complex double iterator(complex double x, complex double c);
