#include <iostream>
using namespace std;


// 2. Looping + Math

int main () {

    //int num;
    //cout<<"Enter a number of the sum of digits: ";
    //cin>>num;

    int num = 1234;

    int dig=0; 

    for(int i = 0; i<4; i++){
        dig = (dig*10) + (num%10);
        num = num/10;
    }

    cout<<dig;

}

