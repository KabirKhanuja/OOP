#include <iostream>
using namespace std;

class Number {
public:
    int x;
    static int sum;
    static int count;

    void read() {
        cin >> x;
        sum += x;
        count++;
    }

    static int average() {
        return sum / count;
    }
};

int Number::sum = 0;
int Number::count = 0;

int main() {
    int n;
    cin >> n;

    Number obj;

    for (int i = 0; i < n; i++) {
        obj.read();
    }

    cout << "Average: " << Number::average();
}