// Program: To check if entered number is armstrong number or not.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
#include<math.h>
int main(){
    int number,originalNumber,sum=0;
    printf("Enter the number: ");
    scanf("%d" , &number);
    originalNumber=number;
    while(number!=0){
        int random = number % 10;
        int random2 = pow(random,3);
        sum += random2;
        number/=10;
    }
    if(sum==originalNumber){
        printf("%d is an armstrong number." , originalNumber);
    }
    else{
        printf("%d is not an armstrong number." , originalNumber);
    }
}
