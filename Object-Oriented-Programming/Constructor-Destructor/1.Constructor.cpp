#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point() {            // default constructor
        x = 0;
        y = 0;
    }
};

int main() {
    Point p;
    cout << p.x << " " << p.y;
}