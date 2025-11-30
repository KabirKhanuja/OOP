#include <iostream>
using namespace std;

// 4. Arrays

// Take N inputs and find the largest number in the array.

int main(){

    int arr[5];
    cout<<"Enter 5 numbers";

    for(int i =0; i<4; i++){
        cout<<"\nEnter number "<<i+1<<" :";
        cin>>arr[i];
    }

    int largest = arr[0];
    for(int i=0; i<4; i++){
        if(largest<arr[i]){
            largest = arr[i];
        }
    }

    cout<<"Largest number is: "<<largest;


    // Take N inputs and find the 2nd-largest number in the array.

}