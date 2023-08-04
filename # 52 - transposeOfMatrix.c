// Program: To transpose a matrix.
// Author: Dev Mehta
// Date: 4th Aug 2023.
#include <stdio.h>

int main() {
    int row, column, i, j;
    printf("Enter the row and column of the matrix: ");
    scanf("%d %d", &row, &column);
    int matrix[row][column];

    printf("Enter the values in the matrix:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("Enter the value of a[%d][%d]: ", (i + 1), (j + 1));
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Transposed matrix:\n");
    for (i = 0; i < column; i++) {
        for (j = 0; j < row; j++) {
            printf("%d ", matrix[j][i]);
        }
        printf("\n");
    }

    return 0;
}
