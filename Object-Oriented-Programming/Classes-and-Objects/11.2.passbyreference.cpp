#include <iostream>
using namespace std;

class Number {
public:
    int x;

    void increment(Number &n) {   // & references to the original object 
    n.x++; 
}
};



int main() {
    Number obj;
    cin >> obj.x;

    cout << "Before: " << obj.x << endl;

    obj.increment(obj); 

    cout << "After: " << obj.x;
}