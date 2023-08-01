// Program: To delete an element in an array in the given array.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
void swap(int *x , int *y){
    int t = *x;
    *x = *y;
    *y = t;
}
int main(){
    int arr[100];
    int size , position ;
    printf("Enter the size of an array: ");
    scanf("%d" , &size);
    printf("Enter the elements of an array(only interger): ");
    for(int i = 0 ; i < size ; i++){
        scanf("%d" , &arr[i]);
    }
    printf("Enter position where you want to delete the element: ");
    scanf("%d" , &position);
     if(position < 0 || position > (size)){
        printf("Enter the correct position.");
    }
    else{
        swap(&arr[position-1] , &arr[size - 1]);
    }
    arr[size-1]='\0';
     printf("New array after deletion : ");
    for(int h = 0 ; h < ( size-1 ) ; h++){
        printf(" %d" , arr[h]);
    }
}