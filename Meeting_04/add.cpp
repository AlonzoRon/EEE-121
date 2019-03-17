#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b){
    return a + b;
}

int main() {
    string s = "s";
    string t = "t";

    double a  = 2.34, b = 3.23;
    cout << add(s, t) << endl;
    cout << add(a, b) << endl;
}
