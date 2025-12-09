#include <iostream>
using namespace std;

class Rectangle {
public:
    int l, b;

    Rectangle(){ // wont be called as no object with zero parameters
        cout<<"created";
    }
    Rectangle(int x, int y) {   // parameterized constructor
        l = x;
        b = y;
    }

    int area() {
        return l * b;
    }
};

int main() {
    int a, b;
    cin >> a >> b;

    Rectangle r(a, b); // have to initialize an object while passing values because constructor will be called only then
    cout << r.area();
}