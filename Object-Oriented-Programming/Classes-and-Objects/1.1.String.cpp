#include <iostream>
#include <string>
using namespace std;

int main(){
    
    string name;
    cout<<"Enter your name: ";
    getline(cin, name);

    string ini = "Mr. ";

    cout<<ini.append(name);
    cout<<"\nFull name length: "<<name.length();

}
