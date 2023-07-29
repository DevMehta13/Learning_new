// Program: To copy a string.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
#include<string.h>//this is used for strcpy.
int main(){
    char source[100],destination[100];
    printf("Enter the string in the source: ");
    fgets(source, sizeof(source), stdin);//try to use this only in case of string instead of scanf.
    strcpy(destination,source);//this is used to copy string from one array to another.
    printf("The copied string in destination is: %s" , destination);
}