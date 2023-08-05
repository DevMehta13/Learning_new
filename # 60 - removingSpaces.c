// Program: To remove all vowels from the string.
// Author: Dev Mehta
// Date: 5 Aug 2023.
#include<stdio.h>
#include<string.h>
int main(){
    int i  , j , count=0 ; 
    char string[100];
    printf("Enter a line of string: ");
    fgets(string, sizeof(string), stdin);
    int len = strlen(string);
    for( i = 0 ; i < len ; i++ ){
        if(string[i] == ' '){
            for( j = i ; j < len ; j++ ){
                string[j] = string[j+1];
                count++;
            }
            i--;
            len--;
        }
        string[len-1] = '\0';
    }
    printf("String after removing spaces: ");
    puts(string);//To print the string.
}