#include <iostream>
using namespace std;

// 4. Arrays

// Take N inputs and find the largest number in the array.

int main(){

 /* int arr[5];
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

*/
    // Take N inputs and find the 2nd-largest number in the array.

    int arr1[5];
    cout<<"Enter 5 numbers";

    for(int i =0; i<5; i++){
        cout<<"\nEnter number "<<i+1<<" :";
        cin>>arr1[i];
    }

    int lar = INT_MIN, seclar=INT_MIN;
    for(int i=0; i<5; i++){
        
        if(lar<arr1[i]){
            seclar = lar;
            lar = arr1[i];
        } else {
            if(arr1[i] != lar && seclar<arr1[i]){ // arr1[i] != lar is for distinct values
                seclar = arr1[i];
            }
            
        }
    }

    cout<<"Largest number is: "<<lar;
    cout<<"\nSecond largest number is: "<<seclar;

}