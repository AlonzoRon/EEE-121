#include<iostream>
using namespace std;

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int a, b;
    a = 10;
    b = 20;

    cout << a << " " << b << endl;
    swap(&a, &b);
    cout << a << " " << b << endl;
}
