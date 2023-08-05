#include <stdio.h>

int main() {
    FILE *file;
    char data[100];
    file = fopen("test1.txt", "r");
    if (file != NULL) {
        if (fgets(data, sizeof(data), file) != NULL) {
            fclose(file);
            printf("Your data was successfully read: %s", data);
        } else {
            printf("Error reading data from the file.");
        }
    } else {
        printf("There was an error in opening the file.");
    }
    return 0;
}
