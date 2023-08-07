#include <stdio.h>

void Roman(int year) {
    int value[] = {1000,  500,  100,  50,  10, 9, 5, 4, 1};
    char *symbol[] = {"M", "D",  "C",  "L",  "X", "IX", "V", "IV", "I"};

    for (int i = 0; year > 0; i++) {
        while (year >= value[i]) {
            printf("%s", symbol[i]);
            year -= value[i];
        }
    }
}
int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printf("year in roman: ");
    Roman(year);
}