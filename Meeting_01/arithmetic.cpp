#include<iostream>
using namespace std;

int main(){

    int x = 10, y = 3;
    float a = 3.14, b = -1;

    cout << x/y << endl; // integer division (because both are integers)
    cout << x/a << endl; // output is float
    cout << (x*a)/y << endl; // output is also float
    //cout << x % a << endl; // not possible because integer and float

}
