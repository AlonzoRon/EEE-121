#include<iostream>
using namespace std;

int main(){
    int n;

    cout << "Enter a small integer: ";
    cin >> n;

    int sum = 0;
    while(n > 0){
        sum = sum + n;
        n = n - 1;
    }
    cout << sum << endl;
}
