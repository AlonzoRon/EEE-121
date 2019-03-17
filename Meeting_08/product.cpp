#include<iostream>
#include<cassert>
using namespace std;

// Assume that a and b are POSITIVE integers
long long int woo(long long int a, long long int b){
    long long int a0 = a, b0 = b;
    
    long long int ans = 0;
    while(a > 0){
        if (a % 2 == 1){
            ans = ans + b;
        }
        a /= 2;
        b *= 2;
        assert(ans + a*b == a0*b0);
    }
    return ans;
}

int main(){
    cout << woo(111111, 222222) << endl;
}
