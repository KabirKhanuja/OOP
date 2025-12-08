#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int age;

    // Function taking object as a parameter
    void compareAge(Student s) {
        if (age > s.age)
            cout << name << " is older than " << s.name << endl;
        else if (age < s.age)
            cout << s.name << " is older than " << name << endl;
        else
            cout << name << " and " << s.name << " are of same age.\n";
    }
};

int main() {
    Student s1, s2;

    s1.name = "Kabir";
    s1.age  = 18;

    s2.name = "Riya";
    s2.age  = 20;

    s1.compareAge(s2);   
}
