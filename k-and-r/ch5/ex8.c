#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month]) {
        return -1;
    }

    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (yearday < 1 || yearday > 365 + leap) {
        *pday = *pmonth = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; ++i) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main(int argc, char *argv[]) {
    int y = atoi(argv[1]);
    int m = atoi(argv[2]);
    int d = atoi(argv[3]);

    int doy = day_of_year(y, m, d);
    int month, day;
    month_day(y, doy, &month, &day);

    printf("original: %d-%d-%d\n", y, m, d);
    printf("day of year: %d\n", doy);
    printf("month/day: %d/%d\n", month, day);

    return 0;
}
