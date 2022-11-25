#include "fractal.h"
#include <stdlib.h>

/* settings.c */   complex double iterator(complex double x, complex double c);
/* self */         void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration);
/* auxiliaryFunctions.c */uint32_t hsl2rgb(double h, double s, double l);
/* self */         uint64_t iterate(complex double z, complex double c, int maxIteration, complex double previous, char initialCall);
/* settings.c */   complex double* colorTableData(complex double* table);
/* settings.c */   uint64_t escapeManager(complex double z, complex double previous, complex double c, int i);
/* render.c */     void generateBitmapImage(unsigned char *image, int height, int width, char *fileName);

/*
this giant function manages everything
renders and save an image
  - topleft - complex number of the image's top left
  - bottomright - complex numer of the image's bottom right 
  - secondParameter
  - mode whether to iterate
  - width - image width in pixels
  - height - image height in pixels
  - seqID - this will be stringified for the filename
  - maxIteration - the maximum amount of iteration for each pixel

*/
void renderFrame(complex double topleft, complex double bottomright, complex double secondParameter, unsigned char mode, int width, int height, int seqID, int maxIteration) {
    // unsigned char image[height][width][3]; 
    // must be on heap to prevent stack overflow
    unsigned char * image = malloc(height * height * 3 * sizeof(unsigned char));

    complex double imagesize = bottomright - topleft;
    complex double pixelDeltaV = cimag(imagesize) / height;
    complex double pixelDeltaH = creal(imagesize) / width;
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            complex double position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            uint64_t pixel = mode ? iterate(position, secondParameter, maxIteration, 0, 1) : iterate(secondParameter, position, maxIteration, 0, 1);
            uint32_t color = hsl2rgb(setfpbits32(pixel), IMAGE_SATURATION, setfpbits32(pixel >> 32)); // be careful, lots of auto type casting
            image[3 * width * h + 3 * w + BLUE]  = color >> 8;
            image[3 * width * h + 3 * w + GREEN] = color >> 16;
            image[3 * width * h + 3 * w + RED]   = color >> 24; // TODO program crashes here for certain image dimensions
        }
    }
    char filename[13];
    for (char exp = 7; exp > -1; exp--) { // base conversion
        filename[exp] = (unsigned char)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = (unsigned char)('.');
    filename[9] = (unsigned char)('b');
    filename[10] = (unsigned char)('m');
    filename[11] = (unsigned char)('p');
    filename[12] = (unsigned char)(0);
    generateBitmapImage((unsigned char *)image, height, width, filename);
    free(image);
    printf("%s rendered\n", filename);
}

// non-recursive version of below function
// uint64_t iterate(complex double z, complex double c, int maxIteration) {
//     for (int i = 0; i < maxIteration; i++) {
//         complex double previous = z;
//         z = iterator(z, c);
//         uint64_t escdef = escapeManager(z, previous, c, i);
//         if(escdef > 0) return escdef;
//     }
//     return 0;
// }

uint64_t iterate(complex double z, complex double c, int maxIteration, complex double previous, char initialCall) {
    if(initialCall) return iterate(iterator(z, c), c, maxIteration - 1, previous, 0);
    if (maxIteration == 0) return 0;

    previous = z;

    uint64_t escdef = escapeManager(z, previous, c, maxIteration);
    if(escdef > 0) return escdef;
    
    return iterate(iterator(z, c), c, maxIteration - 1, previous, 0);
}
