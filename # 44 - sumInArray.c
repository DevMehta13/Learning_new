// Program: To find sum of elements of an array.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
int main(){
    int size,i,sum=0;
    printf("Enter the number of terms: ");
    scanf("%d" , &size);
    int arr[size];
    printf("Enter the elements of an array: \n");
    for(i = 0 ; i < size ; i++){
        scanf("%d" , &arr[i]);
    }
    for(int j = 0 ; j < size ; j++){
        sum += arr[j];
    }
    printf("The sum of elements of an array is: %d " , sum);
}