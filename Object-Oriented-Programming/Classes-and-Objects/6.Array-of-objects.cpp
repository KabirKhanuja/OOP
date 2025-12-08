#include<iostream>
#include<string>
using namespace std;

// Create a Class Box and Find Volume using Array of Objects

class box {
    private:
    int l,b,h;
    
    public:

    void get(int x, int y, int z){
        l = x;
        b = y;
        h = z;

    }

    int vol(){
        return l*b*h;
    }
    
    

};


int main(){


    int n;
    cout<<"Enter number of boxes: ";
    cin>>n;

    box b[n]; // array of objects 

    for(int i =0; i<n; i++){
        int l,br,h; // using br cause b has already been declared as a object
        cout<<"Enter length, breadth, and height: ";
        cin>>l>>br>>h;

        b[i].get(l,br,h);
    }

    for(int i=0; i<n; i++){
        cout<<"\nVolume: "<<b[i].vol();
    }



}