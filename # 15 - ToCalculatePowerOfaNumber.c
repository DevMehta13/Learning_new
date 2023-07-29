// Program: To calculate power of a number.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
#include<math.h>
int main(){
    float base,exponent;
    printf("Enter the base: ");
    scanf("%f" , &base);
    printf("Enter the exponent: ");
    scanf("%f" , &exponent);
    printf("Power of a number is %f" , pow(base,exponent));
}