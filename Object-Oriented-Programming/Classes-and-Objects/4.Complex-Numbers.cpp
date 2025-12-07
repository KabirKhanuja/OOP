#include<iostream>
#include<string>
using namespace std;

// Add Two Complex Numbers (Objects as Parameters & Returning Object)

class addComp {
    public:
    int x,y;

    int add(addComp val){
        cout<<"Expression : ";
        cout<<x+val.x<<"+"<<y+val.y;
    }

};

int main(){


    addComp c1, c2;


    cout<<"Give x,y for poßly1: ";
    cin>>c1.x,c1.y;
    cout<<"\nGive x,y for poly2: ";
    cin>>c2.x,c2.y;

    c1.add(c2);



}