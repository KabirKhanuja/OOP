#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int marks;

    Student(string n, int m) {   // parameterized constructor
        name = n;
        marks = m;
    }

    Student(const Student &s) {  // copy constructor
        name = s.name;
        marks = s.marks;
    }
};

int main() {
    string n;
    int m;
    cin >> n >> m;

    Student s1(n, m);
    Student s2(s1);   // copy constructor is called

    cout << s2.name << " " << s2.marks;
}