// Program: To compare two strings.
// Author: Dev Mehta
// Date: 30th July 2023.
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool compareStrings(char *string1, char *string2) {
    return strcmp(string1, string2) == 0;//strcmp is used to compare the strings.
}

int main() {
    char string1[1000], string2[1000];
    printf("Enter statement 1: ");
    scanf("%s", string1);
    printf("Enter statement 2: ");
    scanf("%s", string2);

    if (compareStrings(string1, string2)) {
        printf("Strings are equal.\n");
    } else {
        printf("Strings are not equal.\n");
    }

    return 0;
}
