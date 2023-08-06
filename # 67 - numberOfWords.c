// Program: To count number of words in the file.
// Author: Dev Mehta
// Date: 6 Aug 2023.
#include<stdio.h>
int main(){
    FILE *file1;
    char fileName[100] , ch  , count = 0 ; 
    printf("Enter the name of file: ");
    scanf("%s" , &fileName);
    file1 = fopen("test14.txt" , "r");
    if( file1 == NULL ){
        printf("ERROR IN OPENING THE FILE.");
    }
    while((ch = fgetc(file1)) != EOF ) {
        if(ch == ' '){
            count++;
        }
    }
    printf("Number of lines in the file is %d" , count+1);
}