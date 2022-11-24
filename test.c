#include <stdio.h>
#include <complex.h>

complex double polynomial(complex double x, complex double *coefficents, int degree) {
    complex double accumulator = coefficents[degree];
    for(degree--; degree > -1; degree--) {
        accumulator = coefficents[degree] + accumulator * x;
    }
    return accumulator;
}

void printComplex(complex double z) {
    printf("%f + i*%f\n", creal(z), cimag(z));
}

int main() {
    complex double coeff[3] = {0, 0, 1};
    for (int i = 0; i < 100; i++) {
        printComplex(
            polynomial(i, coeff, 2)
        );
    }

    return 0;
}