// Program: To store data about weather.
// Author: Dev Mehta
// Date: 31th July 2023.
#include<stdio.h>
struct weather{
    float temperature;
    float windSpeed;
    float chanceOfRain;
};
int main(){
    int size , i;
    printf("Enter the number of places whose data you need: ");
    scanf("%d" , &size);
    struct weather data[size];
    printf("Enter the data of weather(temprature,windspeed and chances of rain): \n");
    for(i = 0 ; i < size ; i++){
        scanf("\n%f %f %f" , &data[i].temperature , &data[i].windSpeed , &data[i].chanceOfRain);
    }
    printf("The data is stored successfully. THANK YOU.");
}