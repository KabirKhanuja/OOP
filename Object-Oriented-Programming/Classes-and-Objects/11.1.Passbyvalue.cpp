#include <iostream>
using namespace std;

class Number {
public:
    int x;

    void increment(Number n) {   
    n.x++; // copy of x so original wont change
    //x++; if i uncomment this, then value would increase 
}
};



int main() {
    Number obj;
    cin >> obj.x;

    cout << "Before: " << obj.x << endl;

    obj.increment(obj); // have to pass object here cause increment's argument takes object only 

    cout << "After: " << obj.x;
}