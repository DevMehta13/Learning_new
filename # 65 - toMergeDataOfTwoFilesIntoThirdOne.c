// Program: To merge data of two file into third one.
// Author: Dev Mehta
// Date: 6 Aug 2023.
#include<stdio.h>
int main(){
    FILE *file1 , *file2 , *file3 ;
    char ch; 
    file1 = fopen("test11.txt" , "r");
    file2 = fopen("test12.txt" , "r");
    file3 = fopen("test13.txt" , "w");
    if( file1 == NULL || file2 == NULL || file3 == NULL){
        printf("ERROR IN OPENING THE FILE.");
        return 0 ;
    }
    while((ch = fgetc(file1)) != EOF ){
        fputc( ch , file3);
    }
    while((ch = fgetc(file2)) != EOF ){
        fputc( ch , file3);
    }
    printf("FILES ARE MERGED SUCCESSFULLY.");
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 1;
}