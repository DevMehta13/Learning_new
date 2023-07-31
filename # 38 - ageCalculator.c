// Program: To calculate the age of a person.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
struct age{
    int day;
    int month;
    int year;
};
int main(){
    struct age currentDate , birthDate ;
    printf("Enter the current date and birthdate in DD MM YYYY format: \n");
    scanf("%d %d %d" , &currentDate.day , &currentDate.month , &currentDate.year);
    scanf("%d %d %d" , &birthDate.day , &birthDate.month , &birthDate.year);
    int age = currentDate.year - birthDate.year;
    if(currentDate.month < birthDate.month || (currentDate.month==birthDate.month && currentDate.day < birthDate.day)){
        age--;
    }
    printf("Your age in years is : %d" , age);
}