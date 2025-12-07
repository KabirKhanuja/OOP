#include<iostream>
#include<string>
using namespace std;

// create a class student to store and display student info for n students now

class student {
    private:
    string name;
    int roll; 
    int marks;

    public:
    void get(string n, int r, int m){
        name = n;
        roll = r;
        marks = m;
    }

    void show(){
        cout<<name<<"\n";
        cout<<roll<<"\n";
        cout<<marks<<"\n";
    }

};

int main(){

    int n;
    cout<<"Enter the number of students: ";
    cin>>n;

    student s[n];

    
    for(int i=0; i<n; i++){
        cout<<"Enter student name, rollno, marks for studnet no. "<<i+1<<": ";
        string name;
        int roll, marks;
        cin>>name>>roll>>marks;
        s[i].get(name, roll, marks);

    }

    for(int i = 0; i<n; i++){
        s[i].show();
    }

}