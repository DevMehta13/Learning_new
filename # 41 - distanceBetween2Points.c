// Program: To find distance between any two points.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
#include<math.h>
struct point{
    float x;
    float y;
};
int main(){
    struct point points[2];
    int i;
    printf("Enter 2 points (x1,y1) and (x2,y2): \n");
    for(i = 0 ; i < 2 ; i++){
        scanf("%f %f" , &points[i].x , &points[i].y);
    }
    float a = (points[0].x - points[1].x);
    float b = (points[0].y - points[1].y);
    float distance = sqrt(pow(a,2) + pow(b,2));
    printf("\nThe distance between two entered points is %f" , distance);
}