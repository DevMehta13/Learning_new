// Program: To store movies data using data strucure.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
struct movies{
    char movieName[100];
    int year;
    int budget;
    int collection;
};
int main(){
    int size,i,j;
    printf("Enter the number of movies data you want to stored: ");
    scanf("%d" , &size);
    struct movies movies[size];
    printf("Enter the name , year of release , budget(in cr) , collection(in cr) of the movie:\n ");
    for( i = 0 ; i < size ; i++){
        scanf("\n%s %d %d %d" , movies[i].movieName , &movies[i].year , &movies[i].budget , &movies[i].collection);
    }
}