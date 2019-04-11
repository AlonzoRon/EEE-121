#include<iostream>
using namespace std;

int main(){
    float a = 10, b = 3, c = 2, d = 200;

    bool x = true;
    char y = 'x';
    int z = 10;
    double w = 12.3;

     // cout << &a << endl;
     // cout << &b << endl;
     // cout << &c << endl;
     // cout << &d << endl;

     cout << sizeof(a) << endl << endl;

     cout << sizeof(x) << endl;
     cout << sizeof(y) << endl;
     cout << sizeof(z) << endl;
     cout << sizeof(w) << endl;

     /*
      float - 4 bytes
      bool - 1 byte
      char - 1 byte
      int - 4 bytes
      double - 8 bytes
      */
}
