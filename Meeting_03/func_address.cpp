#include<iostream>
using namespace std;

int square(int& x){
    cout << "x is at " << &x << endl;
    x = x * x;
    return x;
}

int main(){
    int val = 13;
    cout << "val is at " << &val << endl;

    int tmp = square(13);
    cout << val << endl;
}
