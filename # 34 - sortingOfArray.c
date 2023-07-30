// Program: To sort an array.
// Author: Dev Mehta
// Date: 30th July 2023.
#include<stdio.h>//this program is done using bubble sort method there are several method of doing it we will learn it in dsa see chat gpt.
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
    printf("Array in ascending order is: ");
    for (int a = 0; a < size; ++a) {
        printf("%d ", arr[a]);
    }
}
int dsc(int *arr ,int size){
    for(int j = 0 ; j < size ; ++j ){
        for(int h = j ; h < size ; ++h){
            if(arr[j] > arr[h]){
                swap(&arr[j],&arr[h]);
            }
        }
    }
    printf("\nArray in descending order is: ");
    for (int a = 0; a < size; ++a) {
        printf("%d ", arr[a]);
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
    printf("Array befrore rearrangment: ");
    for (int d = 0; d < size; ++d) {
        printf("%d ", arr[d]);
    }
    printf("\n");
    asc(arr , size);
    dsc(arr , size);
}