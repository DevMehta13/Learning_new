// Program: To find largest number in an array.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
int main(){
    int size,i;
    printf("Enter the size of an array: ");
    scanf("%d" , &size);
    int arr[size];
    printf("Enter the elements in an array: \n");
    for(i = 0 ; i < size ; i++){
        scanf("%d" , &arr[i]);
    }
    int max = arr[0];
    for(int j = 1 ; j < size ; j++){
        if(arr[j] > max ){
            max = arr[j];
        }
        else{
            max = max;
        }
    }
    printf("The maximum value is %d" , max);
}