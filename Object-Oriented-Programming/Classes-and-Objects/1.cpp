#include<iostream>
#include<string>
using namespace std;

// create a class student to store and display student info 

class student {
    public:

    int rollno;
    string name;
    char grade; 
    string subject;

};

int main(){

    student s1, s2;
    s1.rollno = 19;
    s1.name = "Kabir";
    s1.grade = 'A';
    s1.subject = "Maths";
    

    s2.rollno=20;
    s2.name = "Aryan";
    s2.grade = 'B';
    s2.subject = "History";

}