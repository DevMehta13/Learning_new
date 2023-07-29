// Program: To print all prime numbers from 1 to n.
// Author: Dev Mehta
// Date: 28th July 2023.
#include<stdio.h>
int primeno(int n1 ){
    int ans,i,j,isPrime;
    for(i=2 ; i<=n1 ; i++){
        isPrime=1;
        for( j=2 ; j<i ; j++){
            ans = i % j;
            if(ans==0){
            isPrime=0;
            break;
            }
        }
        if(isPrime){
        printf("The prime numbers are: %d\n" , i);
        }
    }
}

int main(){
    int n1;
    printf("Enter the number: ");
    scanf("%d" , &n1 );
    primeno(n1);
    return 0;
}