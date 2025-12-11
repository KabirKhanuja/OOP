#include<iostream>

using namespace std;

class names {
    public:
    string name;
   // int age;

   void stick(names obj){
         string full_name = name + " " + obj.name;
         cout<<full_name;
   }
};

int main() {
    
    names s1, s2;

    cin>>s1.name;
    cin>>s2.name;

    s1.stick(s2);

}