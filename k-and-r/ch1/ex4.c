#include <stdio.h>

int main(void) {
    int lower = 0;
    int upper = 300;
    int step = 20;

    printf("Celsius\tFahrenheit\n");
    float celsius = lower;
    while (celsius <= upper) {
        float fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
