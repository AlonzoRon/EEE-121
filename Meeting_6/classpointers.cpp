#include <iostream>
using namespace std;

class SimpleClass{
public:
    int attrib;
    
    //SimpleClass();
    SimpleClass(int); // states the data type of the input
    SimpleClass* memorylocation();
};

// SimpleClass::SimpleClass(){
//     attrib = 0;
// }

SimpleClass* SimpleClass::memorylocation(){
    return this;
}

SimpleClass::SimpleClass(int attrib){
    // (*this).attrib = attrib;
    this -> attrib = attrib;
    // (*this) == self in python
    // this == self in python
}

int main(){
    SimpleClass S(10);
    cout << S.memorylocation() << endl;
}
