// Program: To write a data into file.
// Author: Dev Mehta
// Date: 5th Aug 2023.
#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *file1;
    char dataToWrite[] = "HELLO HOW ARE YOU.";
    file1 = fopen("test.txt " , "w");
    if(file1 != NULL){
        fprintf(file1,"%s",dataToWrite);
        fclose(file1);
        printf("The data was written successfully.");
    }
    else{
        printf("Unable to open the file.");
    }
}