// Program: To add two matrices.
// Author: Dev Mehta
// Date: 1st Aug 2023.
#include<stdio.h>
int main(){
    int column , row , i , j ;
    printf("Enter rows and columns : ");
    scanf("%d %d" , &row , &column);
    int matrix1[column][row] , matrix2[column][row] , add[column][row];
    printf("Enter the elements of matrix 1:\n ");
    for( i = 0 ; i < row ; i++){
        for( j = 0 ; j < column ; j++){
            printf("Enter the value of a%d%d : " , i + 1 , j + 1);
            scanf("%d" , &matrix1[i][j]);
        }
    }
    printf("Enter the elements of matrix 2: \n");
    for( i = 0 ; i < row ; i++){
        for( j = 0 ; j < column ; j++){
            printf("Enter value of a%d%d : " , i + 1 , j + 1);
            scanf("%d" , &matrix2[i][j]);
        }
    }
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < column ; j++){
            add[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    printf("The sum of the 2 enterd matrix is : \n");
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < column ; j++){
            printf("%d " , add[i][j]);
            if(j == column -1){
                printf("\n");
            }
        }
    }
}