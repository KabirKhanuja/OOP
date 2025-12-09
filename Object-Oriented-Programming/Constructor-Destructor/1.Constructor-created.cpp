#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point() {            
        cout<<"Created";
    }
};

int main() {
    Point p;
}