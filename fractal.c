#include "fractal.h"
#include <stdlib.h>

/* settings.c */   cplxdbl iterator(cplxdbl x, cplxdbl c);
/* auxiliaryFunctions.c */uint32_t hsl2rgb(double h, double s, double l);
/* self */         uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall);
/* settings.c */   uint64_t escapeManager(cplxdbl z, cplxdbl previous, cplxdbl c, int i, cplxdbl orbit);
/* render.c */     void generateBitmapImage(byte *image, int height, int width, char *fileName);

void floatingPointPercisionWarn(cplxdbl topleft, cplxdbl bottomright, double pixelDeltaV, double pixelDeltaH);
void writeFileName(char* dest, int seqID);

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
    byte * image = malloc(width * height * 3 * sizeof(byte));

    cplxdbl imagesize = bottomright - topleft;
    double pixelDeltaV = cimag(imagesize) / height;
    double pixelDeltaH = creal(imagesize) / width;

    floatingPointPercisionWarn(topleft, bottomright, pixelDeltaV, pixelDeltaH);

    cplxdbl previousPosition = NAN + NAN * I;
    uint32_t previousPixelColor;

    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            cplxdbl position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            uint64_t pixel;
            uint64_t color;
            if(IDENTICAL_FP_CACHE && previousPosition == position) {
                color = previousPixelColor;
            } else {
                pixel = mode ? iterate(position, constant, maxIteration, 0, 1) : iterate(constant, position, maxIteration, 0, 1);
                color = hsl2rgb(setfpbits32(pixel), IMAGE_SATURATION, setfpbits32(pixel >> 32)); // be careful, lots of auto type casting
                previousPosition = position;
                previousPixelColor = color;
            }
            image[3 * width * h + 3 * w + BLUE]  = color >> 8;
            image[3 * width * h + 3 * w + GREEN] = color >> 16;
            image[3 * width * h + 3 * w + RED]   = color >> 24;
        }
    }

    char filename[13];
    writeFileName(filename, seqID);

    generateBitmapImage(image, height, width, filename);
    free(image);
    printf("%s rendered\n", filename);
}

uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall) {
    cplxdbl orbit = 0; // may be removed if orbit detection is off
    for(; maxIteration; maxIteration--) {
        previous = z;
        z = iterator(z, c);
        
        if(ORBIT_DETECTION && maxIteration | 1 && !initialCall) {
            orbit = iterator(orbit, c);
        }

        if(maxIteration % ESCAPE_CHECK_FREQ == 0) {
            uint64_t escdef = escapeManager(z, previous, c, maxIteration, orbit);
            if(escdef > 0) return escdef;
        }

    }

    return 0;
}
