// Program: To check if number is even or odd.
// Author: Dev Mehta
// Date: 27th July 2023.
#include<stdio.h>
int main(){
    int a;
    printf("Enter the number: ");
    scanf("%d" , &a);
    if(a%2==0){
        printf("%d is an even number." , a);
    }
    else{
        printf("%d is an odd number." , a);
    }
}