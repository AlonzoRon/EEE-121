#include<iostream>
#include<typeinfo>
using namespace std;

int main(){
    int* p = new int[5];

    int** a = &p;

    int* b = p + 4;
    int c;
    float d;

    cout << typeid(p).name() << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;

    // cout << typeof(p) << endl;
    // cout << typeof(a) << endl;
    // cout << typeof(b) << endl;

}
