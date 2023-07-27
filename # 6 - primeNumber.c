// Program: To check if number is prime 
// Author: Dev Mehta
// Date: 27th July 2023.
#include<stdio.h>
int main(){
    int number,ans;
    printf("Enter the number: ");
    scanf("%d" , &number);
    if(number==0 || number==1){
        printf("Enter valid values.");
    }
    for(int i=2;i<number;++i){
         ans = number % i;
    if(ans==0){
        printf("The %d is not a prime number." , number);
        break;
    }
    else{
        printf("The %d is  a prime number." , number);
        break;
    }
    }
}
