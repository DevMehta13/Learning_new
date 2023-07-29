// Program: To swap numbers using pointers.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int swap(int *a,int *b){
    int t;
    t=*a;
    *a=*b;
    *b=t;
}
int main(){
    int a,b;
    printf("Enter the numbers:");
    scanf("%d %d",&a,&b);
    printf("Before swapping numbers are: %d %d\n" , a ,b);
    swap(&a,&b);
    printf("After swapping numbers are: %d %d", a , b);
}