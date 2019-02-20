#include <iostream>
using namespace std;

// this only works for sorted arrays
bool search(int val, int arr[], int n){
    int left = 0, right = n;
    // invariant: left is valid, right is not
    while(left < right){
        int mid = (left + right) / 2;

        if (arr[mid] == val) return true;
        
        if (val < arr[mid]){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }
    return false;
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(int);
    if(search(100, arr, 10)) cout << "in the array" << endl;
    else cout <<  "not in the array" << endl;
}
