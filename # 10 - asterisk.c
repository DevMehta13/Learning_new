// Program: To print asterisk pattern.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int number;
    printf("Enter the number of asterisk you want to print: ");
    scanf("%d" , &number);
    for(int i=0 ; i<number ; ++i){
        printf("*");
    }
}