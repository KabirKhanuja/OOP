#include <iostream>
using namespace std;

class fetch {

    public:
    int x, y, z;
    
    fetch set(int a, int b) {
        fetch temp;
        temp.x = a;
        temp.y = b;
        temp.z = temp.x + temp.y;
        return temp;   // returning object
    }

};

int main() {
    int a, b;
    cin >> a >> b;

    fetch f, result;
    // storing it in an object result cause cpp can't print object directly
    result = f.set(a, b); 

    // out of the complete object, i can access x,y,z; so rn accessing z
    cout<<result.z;

}