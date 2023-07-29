// Program: To add numbers using pointers.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int a,b;
    int *c,*d;
    printf("Enter two numbers: ");
    scanf("%d %d", &a , &b);
    c = &a;
    d = &b;
    printf("The sum of two numbers is %d" , *c+*d);
}