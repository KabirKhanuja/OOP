#include <iostream>
#include <string>
using namespace std;

int main(){
    
    string name;
    cout<<"Enter your name: ";
    getline(cin, name); // getting the full name including spaces and next word 

    string ini = "Mr. ";

    cout<<ini.append(name); // appending ini + name 
    cout<<"\nFull name length: "<<name.length(); // printing length as well
}
