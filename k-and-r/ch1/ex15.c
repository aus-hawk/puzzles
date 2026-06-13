#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float ftoc(float fahr);

int main(void) {
    float fahr, celsius;

    fahr = LOWER;
    while (fahr <= UPPER) {
        celsius = ftoc(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += STEP;
    }

    return 0;
}

float ftoc(float fahr) {
    return (5.0 / 9.0) * (fahr - 32.0);
}
