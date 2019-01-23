#include <iostream>
using namespace std;

// passing by reference
// int x directly gets edited
int g(int& x, int n){
    x = x * x;
	return (x + 1) % n;
}

// passing by value
// int x in function g only copies the value
// g:x and g:n get born and die in the scope of the function
// int g(int x, int n){

//     x = x * x;
// 	return (x + 1) % n;
// }

int main() {
    int x = 10, n = 3;

    cout << "before funciton call: x = " << x << endl;
    cout << g(x, n) << endl;
    cout << "after funciton call: x = " << x << endl;
}
