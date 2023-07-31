// Program: To store and display dates.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
struct date{
    int day;
    int month;
    int year;
};
int main(){
    int size,i,j;
    printf("Enter the number of dates you wanted to store and display: ");
    scanf("%d" , &size);
    struct date dates[size] ;
    printf("Enter the dates in DD MM YYYY fromat : \n");
    for(i = 0 ; i < size ; i++){
        scanf("\n%d %d %d" , &dates[i].day , &dates[i].month , &dates[i].year);
    }
    printf("The dates you stored are : \n");
    for(j = 0 ; j < size ; j++){
        printf("\n%d %d %d" , dates[j].day , dates[j].month , dates[j].year);
    }
}