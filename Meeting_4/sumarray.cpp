#include<iostream>
using namespace std;

int sum_array(int arr[]){
    int sum = 0;
    for (size_t i = 0; i < 5; i++) {
        sum += arr[i];
    }
    return sum;
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    cout << sum_array(arr) << endl;
}
