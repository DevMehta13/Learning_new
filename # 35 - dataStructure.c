// Program: To create a data structure on students.
// Author: Dev Mehta
// Date: 30th July 2023.
#include<stdio.h>
struct book{
    char name[100];
    int class;
    float percentage;
};
int main(){
    int size,i;
    printf("Enter the number of students whose marks you want to enter: ");
    scanf("%d" , &size);
    struct book b[size];
    printf("Enter the name,class and percentage of students: \n");
    for( i = 0 ; i < size ; i++)
        scanf("\n %s %d %f" , b[i].name , &b[i].class , &b[i].percentage);//here we wont write &b[i].name and just write b[i].name as its string and all so aage se dhyan rakhna.
    printf("The entered data is: \n");
    for(int j = 0 ; j < size ; j++)
        printf("\n%s %d %f" , b[j].name , b[j].class , b[j].percentage);
}
