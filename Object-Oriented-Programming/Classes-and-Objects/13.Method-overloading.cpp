#include <iostream>
using namespace std;

class Area {
public:
    int find(int r) {             // circle
        return 3 * r * r;         // using 3 instead of 3.14 for int output
    }

    int find(int l, int b) {      // rectangle
        return l * b;
    }
};

int main() {
    Area a;
    int r, l, b;

    cin >> r;
    cin >> l >> b;

    cout << "Circle: " << a.find(r) << endl; // completely based off parameters
    cout << "Rectangle: " << a.find(l, b); // arguments matter
}