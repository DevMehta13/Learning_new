// Program: To insert an element in an array in the given array.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
int main(){
    int arr[100];
    int size , position , newElement ;
    printf("Enter the size of an array: ");
    scanf("%d" , &size);
    printf("Enter the elements of an array(only interger): ");
    for(int i = 0 ; i < size ; i++){
        scanf("%d" , &arr[i]);
    }
    printf("Enter the new element's value you want to enter : ");
    scanf("%d" , &newElement);
    printf("Enter position where you want to insert the element: ");
    scanf("%d" , &position);
    if(position < 0 || position > (size)){
        printf("Enter the correct position.");
    }
    else{
        for(int j = size - 1 ; j >= position - 1 ; --j){
        arr[j+1] = arr[j];
        }
        arr[position-1] = newElement;
        }
    printf("New array after insertion : ");
    for(int h = 0 ; h < ( size+1 ) ; h++){
        printf(" %d" , arr[h]);
    }
}