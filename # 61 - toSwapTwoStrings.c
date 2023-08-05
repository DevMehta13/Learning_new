#include <stdio.h>
#include <string.h> 

void swap(char **string1, char **string2) {
    char *temp = *string1;
    *string1 = *string2;
    *string2 = temp;
}

int main() {
    char string1[100], string2[100];
    printf("Enter the string 1: ");
    scanf("%s", string1);
    printf("Enter the string 2: ");
    scanf("%s", string2);

    char *ptr1 = string1;
    char *ptr2 = string2;

    swap(&ptr1, &ptr2);

    printf("Swapped strings:\n");
    printf("%s\n%s", ptr1, ptr2);
    return 0;
}
