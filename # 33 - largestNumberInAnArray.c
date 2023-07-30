// Program: To find largest number in an array.
// Author: Dev Mehta
// Date: 30th July 2023.
#include<stdio.h>
int largestNumber(int *arr , int size){
    int max = arr[0];
    for(int i=1 ; i<size ; ++i){
        if(arr[i] > max){
            max = arr[i];
        }
        else{
            max = max;
        }
    }
    printf("The maximum value in the array is %d" , max);
}
int main(){
    int size;
    printf("Enter the size of an array: ");
    scanf("%d" , &size);
    int arr[size];
    printf("Enter the elements of an array: ");
    for(int i=0 ; i < size ; ++i){
        scanf("%d" , &arr[i]);
    }
    largestNumber(arr,size);
}
