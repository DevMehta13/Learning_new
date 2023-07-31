// Program: To add two complex numbers using data struture.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
struct complexNumber{
    int realPart;
    int imaginaryPart;
}
int main(){
    struct complexNumber numbers[2];
    int i;
    printf("Enter the real and imaginary part of two complex numbers you want to add: \n");
    for( i = 0 ; i < 2 ; i++){
        scanf("\n%d %d" , &numbers[i].realPart , &numbers[i].imaginaryPart);
    }
    printf("Your addition is : ");
    printf("(%d+i%d) + (%d+i%d) = %d+i%d" , numbers[0].realPart , numbers[0].imaginaryPart , numbers[1].realPart , numbers[1].imaginaryPart , numbers[0].realPart+numbers[1].realPart , numbers[0].imaginaryPart+numbers[1].imaginaryPart);
}