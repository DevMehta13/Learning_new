// Program: To print hello world.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int firstTerm=0 , secondTerm=1 , nextTerm , number;
    printf("Enter the number till which you want fibonacci series: ");
    scanf("%d" , &number);
    for(int i=0 ; i<number ; ++i){
        if(i==0){
            printf("%d , " , firstTerm);
            continue;
        }
        if(i==1){
            printf("%d , " , secondTerm);
            continue;
        }
        nextTerm=firstTerm+secondTerm;
        firstTerm=secondTerm;
        secondTerm=nextTerm;
        printf("%d" , nextTerm);
        if(i!=(number-1)){
            printf(" , ");
            
        }
    }
}