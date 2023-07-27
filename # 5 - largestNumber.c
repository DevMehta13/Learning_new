// Program: Program to find greatest number among entered three numbers.
// Author: Dev Mehta
// Date: 27th July 2023.
#include<stdio.h>
int main(){
    int a,b,c;
    printf("Enter any three numbers : ");
    scanf("%d %d %d", &a , &b , &c);
    if(a>=b && a>=c){
        printf("%d is the greatest number among the entered numbers." , a);
    }
    else if(b>=a && b>=c){
        printf("%d is the greatest number among the entered numbers." , b);
    }
    else{
        printf("%d is the greatest number among the entered numbers." , c);
    }
}