// Program: To count numbers of words in the string.
// Author: Dev Mehta
// Date: 5th Aug 2023.
#include<stdio.h>
#include<string.h>
int main (){
    int i , count = 0 ;
    char string[100];
    printf("Enter the string: ");
    fgets(string , sizeof(string) , stdin);
    int len = strlen(string);
    for( i = 0 ; i < len ; i++){
        if(string[i] == ' '){
            count++;

        }
    }
    printf("Number of words are %d" , count+1);
}