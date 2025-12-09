#include <iostream>
using namespace std;

class Box {
public:
    int l, b, h;

    Box(int x = 1, int y = 1, int z = 1) {    // default arguments
        l = x;
        b = y;
        h = z;
    }

    int volume() {
        return l * b * h;
    }

    ~Box() {         // destructor
        cout << "Object destroyed" << endl;
    }
};

int main() {
    int x, y, z;
    cin >> x >> y >> z;

    Box b1(x, y, z);   // param values
    Box b2;            // default values

    cout << b1.volume() << endl;
    cout << b2.volume() << endl;

    // destructor will automatically run at the end
    return 0;
}