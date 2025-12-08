#include <iostream>
using namespace std;

class Marks {
public:
    int m1, m2, m3;
};

class Student {
public:
    int roll;
    string name;
    Marks marks;   // class inside another class
};

int main() {
    int n;
    cin >> n;

    Student s[n]; 

    for (int i = 0; i < n; i++) {
        cin >> s[i].roll >> s[i].name;
        cin >> s[i].marks.m1 >> s[i].marks.m2 >> s[i].marks.m3;
    }

    int topIndex = 0;
    int topTotal = s[0].marks.m1 + s[0].marks.m2 + s[0].marks.m3;

    for (int i = 1; i < n; i++) {
        int total = s[i].marks.m1 + s[i].marks.m2 + s[i].marks.m3;
        if (total > topTotal) {
            topTotal = total;
            topIndex = i;
        }
    }

    cout << s[topIndex].roll << " "
         << s[topIndex].name << " "
         << topTotal;

}