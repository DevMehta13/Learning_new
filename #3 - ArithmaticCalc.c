#include<stdio.h>
int Calc(int number1,int number2,int choice){
    int value;
    switch(choice){
        case 1://Addition
         value = number1 + number2;
        break;
        case 2://Subtraction
         value = number1 - number2;
        break;
        case 3://Multiplication
         value = number1 * number2;
        break;
        case 4://Division
         value = number1 / number2;
        break;
        case 5://To find remainder
         value = number1 % number2;
        break;
    }
    printf("The value of your desired arithmatic operation between two numbers is: %d" , value);
}
int main(){
    int number1,number2,choice;
    printf("WELCOME TO ARITHMATIC_CALCULATOR PERFORM ANY OPERATION YOU WISH.\n");
    printf("--------------------\n");
    printf("Enter the value as per your requirement 1(Addition) , 2(Subtraction) , 3(Multiplication) , 4(Division) , 5(To find remainder): ");
    scanf("%d" , &choice);
    printf("Enter both the numbers: ");
    scanf("%d %d" , &number1 , &number2);
    Calc(number1,number2,choice);
}