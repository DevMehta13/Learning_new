// Program: To multiply two matrices.
// Author: Dev Mehta
// Date: 2nd July 2023.
#include<stdio.h>
int main(){
    int row1 , column1 , row2 , column2 , i , j , h ;
    printf("Enter row and column for matrix 1 : ");
    scanf("%d %d" , &row1 , &column1);
    printf("Enter row and column for matrix 2 : ");
    scanf("%d %d" , &row2 , &column2);
    int matrix1[row1][column1] , matrix2[row2][column2] , result[row1][column2] ;
    if(column1 == row2 ){
        printf("Enter the values of matrix 1 :\n"); 
        for( i = 0 ; i < row1 ; i++){
           for(  j = 0 ; j < column1 ; j++){
              printf("Enter the a[%d][%d]: " , (i+1) , (j+1) );
              scanf("%d" , &matrix1[i][j]);
        }
    }
    printf("Enter the values of matrix 2 :\n"); 
        for( i = 0 ; i < row2 ; i++){
           for(  j = 0 ; j < column2 ; j++){
            printf("Enter the a[%d][%d]: " , (i+1) , (j+1) );
            scanf("%d" , &matrix2[i][j]);
        }
    }
    for( i = 0 ; i < row1 ; i++){
        for( j = 0 ; j < column2 ; j++){
            for( h = 0 ; h < column1 ; h++){
                result[i][j] += matrix1[i][h] * matrix2[h][j] ;  
            }
        }
    }
    for( i = 0 ; i < row1 ; i++){
        for( j = 0 ; j < column2 ; j++ ){
            printf("%d " , result[j][i]);
            if( j == column2 - 1){
                printf("\n");
            }
        }
    }
    }
    else{
        printf("Enter the valid order of matrices. ");
    }
}