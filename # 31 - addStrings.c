// Program: To concatenate two strings using pointers
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
#include<string.h>
char concatenate(char *string1 , char *string2){
    printf("%s%s" , string1 , string2);
}
int main(){
    char string1[100],string2[100];
    printf("Enter your first statement: ");
    scanf("%s" , string1);
    printf("Enter your second statement: ");
    scanf("%s" , string2);
    printf("Statement together is - \n");
    concatenate(&string1,&string2);
}