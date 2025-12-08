#include <iostream>
#include <string>
using namespace std;

// Title: A Date class inside a Person class

// Problem:
// Create two classes:
// 	Date with day, month, year
// 	Person with name and an object of Date representing birthdate

class date{

    public:
    int day, month, year;

};

class person{

    public:
    string name;
    date dob;

};


int main(){
    
    person p;

    cout<< "Enter name: ";
    cin>>p.name;
    cout<<" Enter dob day month year: ";
    cin>>p.dob.day>>p.dob.month>>p.dob.year;

    cout << p.name << " "
    << p.dob.day << "/"
    << p.dob.month << "/"
    << p.dob.year;
    

}
