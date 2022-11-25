#include "fractal.h"
#include <stdlib.h>

/* settings.c */   cplxdbl iterator(cplxdbl x, cplxdbl c);
/* self */         void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl constant, byte mode, int width, int height, int seqID, int maxIteration);
/* auxiliaryFunctions.c */uint32_t hsl2rgb(double h, double s, double l);
/* self */         uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall);
/* settings.c */   cplxdbl* colorTableData(cplxdbl* table);
/* settings.c */   uint64_t escapeManager(cplxdbl z, cplxdbl previous, cplxdbl c, int i);
/* render.c */     void generateBitmapImage(byte *image, int height, int width, char *fileName);

/*
this giant function manages everything
renders and save an image
  - topleft - complex number of the image's top left
  - bottomright - complex numer of the image's bottom right 
  - constant
  - mode whether to iterate
  - width - image width in pixels
  - height - image height in pixels
  - seqID - this will be stringified for the filename
  - maxIteration - the maximum amount of iteration for each pixel

*/
void renderFrame(cplxdbl topleft, cplxdbl bottomright, cplxdbl constant, byte mode, int width, int height, int seqID, int maxIteration) {
    // byte image[height][width][3]; 
    // must be on heap to prevent stack overflow
    byte * image = malloc(height * height * 3 * sizeof(byte));

    cplxdbl imagesize = bottomright - topleft;
    cplxdbl pixelDeltaV = cimag(imagesize) / height;
    cplxdbl pixelDeltaH = creal(imagesize) / width;
    
    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            cplxdbl position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            uint64_t pixel = mode ? iterate(position, constant, maxIteration, 0, 1) : iterate(constant, position, maxIteration, 0, 1);
            uint32_t color = hsl2rgb(setfpbits32(pixel), IMAGE_SATURATION, setfpbits32(pixel >> 32)); // be careful, lots of auto type casting
            image[3 * width * h + 3 * w + BLUE]  = color >> 8;
            image[3 * width * h + 3 * w + GREEN] = color >> 16;
            image[3 * width * h + 3 * w + RED]   = color >> 24; // TODO program crashes here for certain image dimensions
        }
    }

    char filename[13];
    for (char exp = 7; exp > -1; exp--) { // base conversion
        filename[exp] = (byte)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = (byte)('.');
    filename[9] = (byte)('b');
    filename[10] = (byte)('m');
    filename[11] = (byte)('p');
    filename[12] = (byte)(0);

    generateBitmapImage((byte *)image, height, width, filename);
    free(image);
    printf("%s rendered\n", filename);
}

// non-recursive version of below function
// uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration) {
//     for (int i = 0; i < maxIteration; i++) {
//         cplxdbl previous = z;
//         z = iterator(z, c);
//         uint64_t escdef = escapeManager(z, previous, c, i);
//         if(escdef > 0) return escdef;
//     }
//     return 0;
// }

uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall) {
    if(initialCall) return iterate(iterator(z, c), c, maxIteration - 1, previous, 0);
    if (maxIteration == 0) return 0;

    previous = z;

    uint64_t escdef = escapeManager(z, previous, c, maxIteration);
    if(escdef > 0) return escdef;
    
    return iterate(iterator(z, c), c, maxIteration - 1, previous, 0);
}
