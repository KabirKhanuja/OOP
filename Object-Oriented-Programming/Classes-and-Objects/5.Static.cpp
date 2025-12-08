#include<iostream>
#include<string>
using namespace std;

// Employee Salary with Static Count

class salaries {
    private:
    string name;
    int sal;
    
    public:

    int static count;
    void get(string n, int s){
        name = n;
        sal = s;
        count++;
    }

    static int getCount(){
        return count;
    }
    

};

int salaries::count=0;

int main(){


    int n;
    cout<<"Enter number of employees: ";
    cin>>n;

    salaries s[n];

    for(int i =0; i<n; i++){
        
        string name;
        int sal;

        cin>>name;
        cin>>sal;

        s[i].get(name,sal);

    }

    cout<<"Total employees: "<<salaries::getCount();



}