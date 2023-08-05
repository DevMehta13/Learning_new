// Program: To find second largest number in an array.
// Author: Dev Mehta
// Date: 5th Aug 2023.
#include<stdio.h>
int swap(int *arr , int *arr1){
    int t = *arr;
    *arr = *arr1;
    *arr1 = t;
}
int asc(int *arr , int size){
    for(int j = 0 ; j < size ; ++j ){
        for(int h = j ; h < size ; ++h){
            if(arr[j] < arr[h]){
                swap(&arr[j],&arr[h]);
            }
        }
    }
     
}
int main(){
    int size;
    printf("Enter the size: ");
    scanf("%d" , &size);
    int arr[size];
    printf("Enter the elements of an array: ");
    for(int i = 0 ; i < size ; ++i){
        scanf("%d" , &arr[i]);
    }
    asc(arr , size);
    printf("The second largest element of the entered array is %d" , arr[1]);
}