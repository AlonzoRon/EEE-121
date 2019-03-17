#include <iostream>
using namespace std;

int foo(int x, int y){
    int ans = 0;
    while(x > 0) {
        if(x % 2 == 1) {
            ans = ans + y;
        }
    y *= 2;
    x /= 2;
    }
    return  ans;
}

int main(){
    int x, y;
    cin >> x >> y;
    cout << foo(x, y) << endl;
}
