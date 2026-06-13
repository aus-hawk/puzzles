#include <stdio.h>

int main(void) {
    int lower = 0;
    int upper = 300;
    int step = 20;

    printf("Fahrenheit\tCelsius\n");
    float fahr = lower;
    while (fahr <= upper) {
        float celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%10.0f\t%7.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
