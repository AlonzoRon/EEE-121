#include<iostream>
#include<algorithm>
using namespace std;

int bubble_sort(int arr[], int n){
    int count = 0;
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j + 1]);
                count += 1;
            }
        }
    }
    return count;
    
}

int insertion_sort(int arr[], int n){
    int count = 0;
    for(int i = 1; i < n; i++){
        int j = i;
        
        while(j > 0 && arr[j - 1] > arr[j]){
            swap(arr[j - 1], arr[j]);
            count += 1;
            j--;
        }
    }
    return count;
}

int main(){
    int arr[20];
    //int arr1[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
    int arrlong[] = {14, 8, 13, 20, 18, 11, 10, 19, 12, 15, 17, 5, 16, 3, 7, 6, 4, 2, 9 ,1};

    // cout << bubble_sort(arr1, 10) << endl;
    cout << bubble_sort(arrlong, 20) << endl;
    // cout << insertion_sort(arr1, 10) << endl;

    
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 20; j++){
            cin >> arr[j];
        }
        cout << "line " << i + 1 << ": " << bubble_sort(arr, 20) << endl;
    
        // do something here
    }
}
