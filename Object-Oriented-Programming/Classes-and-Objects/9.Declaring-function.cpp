#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    void set(int a, int b); // declaring function
    void show(); 
};

void Point::set(int a, int b) { // function definition outside of the class
    x = a;
    y = b;
}

void Point::show() {
    cout << x << " " << y;
}

int main() {
    Point p;
    p.set(10, 20);
    p.show();
}
