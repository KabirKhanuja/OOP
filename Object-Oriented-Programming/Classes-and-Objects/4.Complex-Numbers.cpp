#include<iostream>
#include<string>
using namespace std;

// Add Two Complex Numbers (Objects as Parameters & Returning Object)

class addComp {
    public:
    int real,img;

    void set(int x, int y){
        real = x;
        img = y;
    }

    int add(addComp val){
        cout<<"Expression : ";
        cout<<real+val.real<<"+"<<img+val.img<<"i";
    }

};

int main(){


    addComp c1, c2;
    int r1,i1,r2,i2;

    cout<<"Give x,y for poly1: ";
    cin>>r1>>i1;
    cout<<"\nGive x,y for poly2: ";
    cin>>r2>>i2;

    c1.set(r1,i1);
    c2.set(r2,i2);

    c1.add(c2);



}