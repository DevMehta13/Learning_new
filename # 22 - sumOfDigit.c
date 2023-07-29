// Program: To check if entered year is leap year or not.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int number,sum;
    printf("Enter the number: ");
    scanf("%d" , &number);
    while(number!=0){
        sum+=(number%10);
        number/=10;
    }
    printf("The sum of digits is %d" , sum);
}