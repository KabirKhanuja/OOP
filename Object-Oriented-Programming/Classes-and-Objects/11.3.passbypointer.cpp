#include <iostream>
using namespace std;

class Number {
public:
    int x;

    void increment(Number *n) {   // using pointer 
    n->x++; // pointing to original
}
};



int main() {
    Number obj;
    cin >> obj.x;

    cout << "Before: " << obj.x << endl;

    obj.increment(&obj); // sending address

    cout << "After: " << obj.x;
}