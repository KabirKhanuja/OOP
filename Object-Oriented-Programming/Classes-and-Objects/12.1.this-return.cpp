#include <iostream>
using namespace std;

class Number {
public:
    int x;

    int setValue(int x) {
        this->x = x;   
        return this->x; // return updated value
    }
};

int main() {
    Number n;
    int a;
    cin >> a;

    int result = n.setValue(a); // store returned value
    cout << result;
}
