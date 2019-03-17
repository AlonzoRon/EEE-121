#include <iostream>
#include <array>
#include "BST.h"
using namespace std;

int main(){
    array<int, 10> arr = {7, 10, 4, 5, 9, 3, 2, 6, 8, 1};
    
    BSTree T;
    
    for(auto x : arr){
        T.insert(x);
    }
    
    T.print();  // should print: 1 2 3 4 5 6 7 8 9 10
}