#include <iostream>
using namespace std;

/*

Compare two objects using pass-by-reference

Problem:

Create class Student with name and marks.
Write a function compare(Student &a, Student &b) 
that returns the student with higher marks (return object by value, 
but comparison via reference).

*/

class student {
public:
    string name;
    int marks;

    student compare (student &a, student &b ){
        if(a.marks > b.marks){
            return a;
        }else{
            return b;
        }
    }
};




int main() {
    student s1, s2, result;

    cout<<"Enter name marks of studnet 1 : ";
    cin>>s1.name>>s1.marks;
    cout<<"Enter name marks of student 2 : ";
    cin>>s2.name>>s2.marks;

    result = result.compare (s1,s2);

    cout<< result.name << " " << result.marks;

}