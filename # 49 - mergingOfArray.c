// Program: To merge two arrays in third array.
// Author: Dev Mehta
// Date: 1st Aug 2023.
#include<stdio.h>
int main(){
    int size1,size2,i,j,h;
    printf("Enter size of both the array: ");
    scanf("%d %d" , &size1 , &size2);
    int arr1[size1] , arr2[size2];
    printf("Enter the value of elements in 1st array and then 2nd array respectively: \n");
    for(int a = 0 ; a < size1 ; a++){
        scanf("%d" , &arr1[a]);
    }
    for(int b = 0 ; b < size1 ; b++){
        scanf("%d" , &arr2[b]);
    }
    int merged[(size1 + size2)];
    for( i = 0 ; i < size1 ; i++){
        merged[i] = arr1[i];
    }
    for( j = 0 ; j < size2 ; j++){
        merged[i + j] = arr2[j];
    }
    printf("The merged array will be : ");
    for( h = 0 ; h < (size1+size2) ; h++){
        printf(" %d" , merged[h]);
    }
}