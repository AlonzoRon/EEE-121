#include<iostream>
#include<typeinfo>
using namespace std;

int main(){
    int* ptr[5]; // created array (unititialized array of ptrs)

    for (size_t i = 0; i < 5; i++) {
        ptr[i] = new int;
    }
    for (size_t i = 0; i < 5; i++) {
        cout << &ptr[i] << endl;
    }
}
