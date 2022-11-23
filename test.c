#include <stdio.h>

int main() {
    for (int i = 0; i < 100; i++) {
        int seqID = i;
        char filename[12];
        for (char exp = 7; exp > -1; exp--)
        {
            filename[exp] = (unsigned char)(48 + seqID % 10);
            seqID /= 10;
        }
        filename[8] = 0x2e; // .
        filename[9] = 0x62; // b
        filename[10] = 0x6d;// m
        filename[11] = 0x70;// p
        printf("%s\n", filename);
    }

    return 0;
}