#include<iostream>
#include "container.h"
using namespace std;

int main(){
    Container<int> C;
    
    for(int i = 1; i <= 100000; i++){
        C.insert(i);
    }

    // for(int i = 0; i <  C.size(); i++){
    //     cout << C[i] << endl;
    // }
}
    
