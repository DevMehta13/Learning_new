// Program: To find frequency in an array.
// Author: Dev Mehta
// Date: 5 Aug 2023.
#include<stdio.h>
int main(){
    int size , number , i , count = 0 ;
    printf("Enter the size of array: ");
    scanf("%d" , &size);
    int arr[size];
    printf("Enter the elements of an array: ");
    for(  i = 0 ; i < size ; i++){
        scanf("%d" , &arr[i]);
    }
    printf("Enter the number whose frequency you need: ");
    scanf("%d" , &number);
    for( i = 0 ; i < size ; i++){
        if(number == arr[i]){
            count++;
        }
    }
    printf("The frequency of number in the array is %d " , count);
}