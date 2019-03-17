#include<iostream>
using namespace std;

template<typename T>
void copy_array(T* dest, T* src, int n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main(){
    double arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double arr2[8];

    copy_array(arr2, arr, 8);

    for (size_t i = 0; i < 8; i++) {
        cout << arr2[i] << " ";
    }
}
