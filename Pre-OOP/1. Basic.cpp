#include <iostream>
using namespace std;

// basic brushing up for oop

// 1. Basic I/O + Conditionals

int main() {

    int a,b;
    cout<<"Enter two numbers: ";
    cin>>a>>b;
    if(a<0){
        cout<<"Enter a positive number: ";
        cin>>a;
    }

    cout<<"Sum is: "<< a+b;

}

