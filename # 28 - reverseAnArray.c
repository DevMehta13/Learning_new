// Program: To reverse an array using pointer.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int main(){
    int size,*lastTerm;
    printf("Enter the size of an array: ");
    scanf("%d" , &size);
    int arr[size];
    printf("\nEnter the %d elements in an array: " , size);
    for(int i=0 ; i<size ; ++i){
        scanf("%d" , &arr[i]);
    }
    lastTerm = &arr[size-1];
    printf("\nThe reversed array is: ");
    for(int n=0 ; n<size ; ++n){
        printf(" %d " , *lastTerm--);
    }
}