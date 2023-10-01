#include<iostream>
using namespace std;
int i , j = 0 ;
int main(){
    int size;
    cout << "Enter the size of an array:- " ;
    cin >> size;
    int arr[size];
    cout<<"Enter the elements of the array:- ";
    for(i = 0 ; i < size ; i++){
        cin>>arr[i];
    }
    for(i = 0 ; i < size ; i++){
        j = j ^ arr[i];
    }
    cout<<"The unique number is "<<j;
}