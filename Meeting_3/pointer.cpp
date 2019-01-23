#include<iostream>
using namespace std;

int main(){
    int var = 3;
    int* p_var = &var;

    cout << var << endl;
    cout << *p_var << endl;

    // & means get address in reference to
    // * means read address
    // dereferencing operator

    *p_var = 10;

    cout << var << endl;
    cout << *p_var << endl;

}
