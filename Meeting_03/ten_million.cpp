#include<iostream>
using namespace std;

int main(){
    int* arr;
    cout << arr << endl;

    arr = new int[10000000];
    cout << arr << endl;
    // int arr[10000000];
    // cout << arr[999999999] << endl;

    delete[] arr;
    cout << arr << endl;
}
