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

    Student* arr = new Student[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i].roll >> arr[i].name;
        cin >> arr[i].marks.m1 >> arr[i].marks.m2 >> arr[i].marks.m3;
    }

    int topIndex = 0;
    int topTotal = arr[0].marks.m1 + arr[0].marks.m2 + arr[0].marks.m3;

    for (int i = 1; i < n; i++) {
        int total = arr[i].marks.m1 + arr[i].marks.m2 + arr[i].marks.m3;
        if (total > topTotal) {
            topTotal = total;
            topIndex = i;
        }
    }

    cout << arr[topIndex].roll << " "
         << arr[topIndex].name << " "
         << topTotal;

    delete[] arr;
}