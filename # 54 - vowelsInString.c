// Program: To find number of vowels in a string.
// Author: Dev Mehta
// Date: 5 Aug 2023.
#include<stdio.h>
int main(){
    int vowels , i ;
    char string[100];
    printf("Enter a line of string: ");
    fgets(string, sizeof(string), stdin);
    for( i = 0 ; string[i] != '\0' ; i++){
        if(string[i] == 'a' || string[i] == 'e' || string[i] == 'i' ||
        string[i] == 'o' || string[i] == 'u'){
            vowels++;
        }
    }
    printf("The number of vowels in the string is %d." , vowels);
}