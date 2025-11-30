#include <iostream>
using namespace std;


// 2. Looping + Math

int main () {

    //int num;
    //cout<<"Enter a number of the sum of digits: ";
    //cin>>num;

    int num = 1234;

    int dig; 

    for(int i = 0; i<4; i++){
        dig = (dig*10) + (num%10);
        num = num/10;
    }

    cout<<dig;

}

// 3. Functions

// 4. Arrays

// 5. Strings

// 6. Pointers

// 7. Pass by Reference

// 8. Dynamic Memory

// 9. Vector + STL Basics

// 10. File Handling