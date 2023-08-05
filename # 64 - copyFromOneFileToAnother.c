// Program: To copy contents of one file to another.
// Author: Dev Mehta
// Date: 5 Aug 2023.
#include<stdio.h>
int main(){
    FILE *sourceFile , *destinationFile ;
    char ch;
    sourceFile = fopen("test10.txt" , "r");
    if( sourceFile == NULL){
        printf("ERROR IN READING THE SOURCE FILE.");
        return 1;
    }
    destinationFile = fopen("test20.txt" , "w");
    if( destinationFile == NULL){
        printf("ERROR WHILE WRITING IN THE DESTINATION. ");
        fclose(sourceFile);//it is necessarry to close this file because isko apan return kar rahe hai idhar hum tab aa rahe hai jab source file successfully read ho gyi ho to ye khatam karne ke pehle use close to karna padega.
        return 1;
    }
    //ch = fgetc(sourceFile);//fgetc is used to copy file's data by single character at time.
    while( (ch = fgetc(sourceFile)) != EOF){//EOF means end of file.
    fputc(ch , destinationFile);//fputc is used to intake the ch value in the destinationFile.
    }
    fclose(sourceFile);
    fclose(destinationFile);
    printf("DATA COPIED SUCCESSFULLY");
    return 0;
}