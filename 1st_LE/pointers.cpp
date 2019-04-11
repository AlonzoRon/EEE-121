#include<iostream>
using namespace std;

int main(){
    int x = 10;

    cout << x << endl;

    int *ptr_x = &x;

    cout << ptr_x << endl;
    cout << *ptr_x << endl;

    int **ptr_y = &ptr_x;

    *ptr_x += 10;
    **ptr_y += 10;

    cout << x << endl;


}
