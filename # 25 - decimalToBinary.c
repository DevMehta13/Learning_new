// Program: To convert decimal form to binary form.
// Author: Dev Mehta
// Date: 29th July 2023.
#include<stdio.h>
#include<math.h>
int main(){
    int number,ans=0,i=0;
    printf("Enter the number whose you want ab binary form: ");
    scanf("%d", &number);
    while(number!=0){
        int bit=number&1;
        ans=(bit*pow(10,i))+ans;
        number=number>>1;
        ++i;
    }
    printf("The binary form is : %d", ans);
    return 0;
}