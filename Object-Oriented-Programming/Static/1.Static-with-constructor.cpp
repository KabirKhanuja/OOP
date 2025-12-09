#include <iostream>
using namespace std;

class Counter {
public:
    static int count;

    Counter() {
        count++;
    }
};

int Counter::count = 0;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Counter c; // everytime object is created constructor is called ; life of object is till the end of iteration
    }

    cout << "Total objects: " << Counter::count;
}