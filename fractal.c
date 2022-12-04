#include "fractal.h"
#include <stdlib.h>

/* settings.c */   cplxdbl iterator(cplxdbl x, cplxdbl c);
/* auxiliaryFunctions.c */uint32_t hsl2rgb(double h, double s, double l);
/* self */         uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall);
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
    byte * image = malloc(width * height * 3 * sizeof(byte));

    cplxdbl imagesize = bottomright - topleft;
    double pixelDeltaV = cimag(imagesize) / height;
    double pixelDeltaH = creal(imagesize) / width;

    double fpdelta_real = fmax( // in case the frame crosses exponents
            fabs(creal(topleft) - setfpbits64(getfpbits64(creal(topleft)) ^ 0x1)),
            fabs(creal(bottomright) - setfpbits64(getfpbits64(creal(bottomright)) ^ 0x1))
        );
    double fpdelta_imag = fmax(
            fabs(cimag(topleft) - setfpbits64(getfpbits64(cimag(topleft)) ^ 0x1)),
            fabs(cimag(bottomright) - setfpbits64(getfpbits64(cimag(bottomright)) ^ 0x1))
        );

    if(fpdelta_imag * FP_INEXACT_WARNING_COEFFICENT >= fabs(pixelDeltaV)) {
        printf("potential floating point impercision. imag-axis avg r/p %f\n", fabs(pixelDeltaV) / fpdelta_imag);
    }
    if(fpdelta_real * FP_INEXACT_WARNING_COEFFICENT >= fabs(pixelDeltaH)) {
        printf("potential floating point impercision. real-axis avg r/p %f\n", fabs(pixelDeltaH) / fpdelta_real);
    }


    for (int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            cplxdbl position = topleft 
                + pixelDeltaV * h * I
                + pixelDeltaH * w;
            uint64_t pixel = mode ? iterate(position, constant, maxIteration, 0, 1) : iterate(constant, position, maxIteration, 0, 1);
            uint32_t color = hsl2rgb(setfpbits32(pixel), IMAGE_SATURATION, setfpbits32(pixel >> 32)); // be careful, lots of auto type casting
            image[3 * width * h + 3 * w + BLUE]  = color >> 8;
            image[3 * width * h + 3 * w + GREEN] = color >> 16;
            image[3 * width * h + 3 * w + RED]   = color >> 24;
        }
    }

    char filename[13];
    for (char exp = 7; exp > -1; exp--) { // base conversion
        filename[exp] = (byte)(48 + seqID % 10);
        seqID /= 10;
    }
    filename[8] = (byte)'.';
    filename[9] = (byte)'b';
    filename[10] = (byte)'m';
    filename[11] = (byte)'p';
    filename[12] = (byte)0;

    generateBitmapImage(image, height, width, filename);
    free(image);
    printf("%s rendered\n", filename);
}

// non-recursive calls must pass 1 to initialCall and/or NAN to previous
// uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall) {
//     if(initialCall) previous = NAN;

//     uint64_t escdef = escapeManager(z, previous, c, maxIteration);
//     if(escdef > 0) return escdef;
    
//     if(maxIteration == 0) return 0;
//     return iterate(iterator(z, c), c, maxIteration - 1, z, 0);
// }

uint64_t iterate(cplxdbl z, cplxdbl c, int maxIteration, cplxdbl previous, char initialCall) {
    for(; maxIteration; maxIteration--) {
        previous = z;
        z = iterator(z, c);
        
        uint64_t escdef = escapeManager(z, previous, c, maxIteration);
        if(escdef > 0) return escdef;

    }

    return 0;
}
