// Program: To check if an entered string is palindrom or not.
// Author: Dev Mehta
// Date: 1st aug 2023.
#include<stdio.h>
#include<string.h>
int main(){
    int size;
    printf("Enter the size of letter: ");
    scanf(" %d" , &size);
    char str[size],reverse[size];
    printf("Enter the the word: ");
    for(int j = 0 ; j < size ; j++)
        scanf(" %c" , &str[j]);
    for(int i = 0 ; i < size ; i++)
        reverse[i] = str[size - 1 - i];
    reverse[size] = '\0';
    if(strcmp(str , reverse) == 0)
        printf("It is a palindrom.");
    else
        printf("It is not a palindrom.");
}