#include <iostream>
using namespace std;

class Number {
public:
    int x;
};

void increment(Number n) {   
    n.x++;
}

int main() {
    Number obj;
    cin >> obj.x;

    cout << "Before: " << obj.x << endl;

    increment(obj);

    cout << "After: " << obj.x;
}