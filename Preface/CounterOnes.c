#include <stdio.h>
#include <string.h>

#define POW(c) (1 << (c)) //2^c
#define MASK(c) (((unsigned short) -1) / (POW(POW(c)) + 1))
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))

int main() {
    printBinary(20743);
    printf("\n");
    printBinary(MASK(0));
    printf("\n");
    printBinary((20743) & MASK(0));
    printf("\n");
    printBinary((20743) >> POW(0) & MASK(0));
    printf("\n");
    printBinary(ROUND(20743,0));
    printf("\n");
    return 0;
}
