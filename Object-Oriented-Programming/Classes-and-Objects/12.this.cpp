#include <iostream>
using namespace std;

class Number {
public:
    int x;

    void setValue(int x) {
        this->x = x;   // using this keyword
    }
};

int main() {
    Number n;
    int a;
    cin >> a;

    n.setValue(a);
    cout << n.x;
}