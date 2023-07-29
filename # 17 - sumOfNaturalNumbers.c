// Program: To get sum of n natural numbers.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int number,sum;
    printf("Enter the number till you want sum of natural numbers: ");
    scanf("%d" , &number);
    sum = (number*(number+1))/2;
    printf("The sum of natural numbers is: %d" , sum);
}