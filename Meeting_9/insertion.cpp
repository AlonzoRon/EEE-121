#include <iostream>
using namespace std;

void insertion_sort(int arr[], int n){
    for(int i = 0; i < n; i++){
    int marker = i;
        if(arr[i + 1] < arr [i]){
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        for(int r = i - 1; r > 0; r--){
            if(arr[r] < arr[r - 1]){
                int temp = arr[r];
                arr[r] = arr[r - 1];
                arr[r - 1]  = temp;
            }
        }
    }
}

int main(){
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    insertion_sort(arr, 10);
    for(int i = 0; i < 10; i++){
        cout << arr[i] << endl;
    }
}
