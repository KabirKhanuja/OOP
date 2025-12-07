#include<iostream>
#include<string>
using namespace std;

// Find Area of Rectangle Using a Class

class rectangle {
    private:
    string name;
    int length; 
    int breadth;

    public:
    void set(int l, int b){
        length = l;
        breadth = b;
    }

    int area(){
        return length*breadth;
    }

};

int main(){

    int l,b;
    cout<<"Enter length and breadth: ";
    cin>>l>>b;


    rectangle r;
    
    r.set(l,b);
    cout<<"Area: "<<r.area();

}