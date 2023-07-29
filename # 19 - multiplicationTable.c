// Program: To print multiplication table.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int number;
    printf("Enter the number whose table you want to print: ");
    scanf("%d" , &number);
    for(int i=1;i<=10;++i){
        printf("%d * %d = %d\n" , number , i , number*i);
    }
}