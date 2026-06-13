#include <stdio.h>

#define swap(t,x,y) do {t temp; temp = x; x = y; y = temp;} while(0)

int main(void) {
    double a = 1.23;
    double b = 4.56;

    printf("%f, %f\n", a, b);

    swap(double, a, b);

    printf("swapped: %f, %f\n", a, b);

    return 0;
}
