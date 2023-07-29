// Program: To check if entered year is leap year or not.
// Author: Dev Mehta
// Date: 29th July 2023.
#include <stdio.h>

int main(){ 
    int number,digit,ans=0;
    printf("Enter the number: ");
    scanf("%d" , &number );
    printf("Number before reversing: \n");
    printf("%d\n" , number );
    while(number!=0){
        digit=number%10;
        ans=ans*10+digit;
        number/=10;
    }
    printf("Number after reversing: \n");
    printf("%d" , ans);
}