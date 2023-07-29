// Program: To find length of string using pointer. 
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int stringLength(const char *string1 ){//idhar bhi *string1 use kiya hai but niche &string1 se call nahi kiya hai.
    int length=0;
    while(*string1 != '\0'){// \0 indicates last element of string.
        length++;
        string1++;
    }
    return (length);
}
int main(){
    char string1[1000];//to write statement we need to form an array and we will pass array in the function and will get its length.
    printf("Enter the statement whose length you wanna find: ");
    fgets(string1, sizeof(string1), stdin);//fgets is used to count length of string even including space.stdin is used to read data from the user through the command-line or terminal.fgets is used to read a line of text (including spaces) from stdin and stores it as a string. It reads until it encounters a newline character (\n) or reaches the specified maximum length.
    int length = stringLength(string1);
    printf("The size of the string is: %d" , length);
}
