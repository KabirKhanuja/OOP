#include <iostream>
using namespace std;

class Employee {
public:
    string name;
    int salary;
    static int richCount;

    void read() {
        cin >> name >> salary;
        if (salary > 50000)
            richCount++;
    }
};

int Employee::richCount = 0;

int main() {
    int n;
    cin >> n;

    Employee e;

    for (int i = 0; i < n; i++) {
        e.read();
    }

    cout << "Rich: " << Employee::richCount;
}