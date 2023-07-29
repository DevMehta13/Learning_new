// Program: To check if number is pallindrom or not.
// Author: Dev Mehta
// Date: 29th July 2023.
#include <stdio.h>

int main(){ 
    int number,digit,ans=0,originalNumber;
    printf("Enter the number: ");
    scanf("%d" , &number );
    originalNumber=number;
    while(number!=0){
        digit=number%10;
        ans=ans*10+digit;
        number/=10;
    }
    if(originalNumber==ans){
        printf("The number is a pallindrom.");
    }
    else{
        printf("The number is not a pallindrom.");
    }
}