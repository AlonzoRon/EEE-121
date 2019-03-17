#include <iostream>
using namespace std;

int main(){
    int var = 3;
    // int arr[13]; // int array of 13 elements

    // cout << sizeof(arr) << endl;
    // cout << 52 / 13 << endl;

    double arr[] = {1, 2, 3, 4, 5, 6, 7};

    cout << arr << endl;

    for (int i = 0; i < 7; i++) {
        arr[i] += 2;
        cout << &arr[i] << endl;
    }

    for (size_t i = 0; i < 7; i++) {
        cout << arr[i] << endl;
    }

    cout << &arr[10] << endl;
    cout << arr + 4 << endl;
}
