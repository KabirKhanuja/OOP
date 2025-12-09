#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int roll;

    static int nextID;

    void read() {
        cin >> name;
        roll = nextID;
        nextID++;
    }

    void print() {
        cout << roll << " " << name << endl;
    }
};

int Student::nextID = 101;

int main() {
    int n;
    cin >> n;

    Student* arr = new Student[n];

    for (int i = 0; i < n; i++) {
        arr[i].read();
    }

    for (int i = 0; i < n; i++) {
        arr[i].print();
    }

    delete[] arr;
}