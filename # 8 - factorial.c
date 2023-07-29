// Program: To print all prime numbers from 1 to n.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int factorial(int number){
    if(number==1){
        return 1;
    }
    else{
    int fac = number * factorial(number-1);
    return (fac);
    }
}
int main(){
    int number;
    printf("Enter any number: ");
    scanf("%d" , &number);
    int fact = factorial(number);
    printf("The factorial of a number is %d" , fact);
}
