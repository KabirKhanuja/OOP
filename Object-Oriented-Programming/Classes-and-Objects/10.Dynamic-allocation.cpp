#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int marks;
};

int main() {
    int n;
    cin >> n;

    Student* arr = new Student[n];   // dynamic array of objects

    for (int i = 0; i < n; i++) {
        cin >> arr[i].name >> arr[i].marks;
    }

    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].marks > arr[idx].marks)
            idx = i;
    }

    cout << arr[idx].name << " " << arr[idx].marks;

    delete[] arr;                     // free memory
    return 0;
}