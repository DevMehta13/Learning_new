// Program: To get sum of diagonal elements of an array.
// Author: Dev Mehta
// Date: 5th Aug 2023.
#include<stdio.h>
int main(){
    int row , column  , i , j  , sum = 0 ;
    printf("Enter the number of row and column:  ");
    scanf("%d %d" , &row , &column);
    if(row == column){
        int matrix[row][column];
    printf("Enter the elements of matrix 1 : \n");
    for( i = 0 ; i < row ; i++){
        for( j = 0 ; j < column ; j++){
            printf("Enter the value of a[%d][%d]: " , i+1 , j+1 );
            scanf("%d" , &matrix[i][j]);
        }
    }
    for( i = 0 ; i < row ; i++){
        for( j = 0 ; j < column ; j++){
            if( i == j){
                sum += matrix[i][j];
            }
        }
    }
    printf("Sum of diagonal elements of matrix is %d." , sum);
    }
    else{
        printf("It should be square matrix kindly enter valid order of matrix.");
    }
    
}