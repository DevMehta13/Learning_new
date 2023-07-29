// Program: To get LCM of two numbers.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
int findLCM(int first, int second){
    for(int i=1; i < second; i++)
        if((first*i)%second == 0) return (first*i);
    return first*second;
}
int main(){
    printf("%d ",findLCM(27, 6));
}
