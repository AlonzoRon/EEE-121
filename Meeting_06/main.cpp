#include <iostream>
#include "container.h"
using namespace std;

int main(){
    Container<string> C;
    
    C.insert("string");
    C.insert("sting");
    C.insert("ring");
    C.insert("sing");
    
    C.insert("some string to be removed");
    C.remove_last();
    
    // Complete remove_last() and size() functions first
    // This for-loop must only print "string sting ring sing"
    for(int i = 0; i < C.size(); i++){
        cout << C[i] << " ";
    }
    cout << endl;
    
    C.remove_last();
    
    // Complete find() first
    // This if-else block must print "not found"
    if (C.find("sing")){
        cout << "found" << endl;
    }
    else{
        cout << "not found" << endl;
    }
}