// Program: To count number of terms.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int count,number,originalNumber;
    printf("Enter the number: ");
    scanf("%d" , &number);
    originalNumber=number;
    while(number!=0){
        number/=10;
        ++count;
    }
    printf("The number of digits in the %d is %d" , originalNumber ,  count);
}