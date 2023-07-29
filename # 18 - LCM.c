#include<stdio.h>
int findLCM(int first, int second){
    int counter = 1, lcm = 1;

    while (lcm >= (first*second)){
        lcm = first*(counter++);
        if(lcm%second == 0) return lcm;
    }
    return first*second;
}
int main(){
    printf("%d ",findLCM(3, 18));
}
