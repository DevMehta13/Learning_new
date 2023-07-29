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
    scanf("%s" , string1);//its %s for string.
    int length = stringLength(string1);
    printf("The size of the string is: %d" , length);
}