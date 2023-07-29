// Program: To swap the numbers.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int a,b;
    printf("Enter the numbers: ");
    scanf("%d %d", &a, &b);
    printf("Numbers before swapping: %d %d\n" , a , b);
    a=a+b;
    b=a-b;
    a=a-b;
    printf("Numbers after swapping: %d %d" , a , b );
}
