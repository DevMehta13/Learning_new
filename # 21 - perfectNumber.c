// Program: To check if number is perfect number is not. 
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int number,sum=0,originalNumber;
    printf("Enter the number: ");
    scanf("%d" , &number);
    originalNumber=number;
    for(int i=1;i<=number/2;++i){
        if(number%i==0){
            sum+=i;
        }
    }
    if(sum==originalNumber){
        printf("%d is a perfect number." , number);
    
    }
    else{
        printf("%d is not a perfect number." , number);
       
    }
    
}