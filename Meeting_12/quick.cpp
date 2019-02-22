#include<iostream>
using namespace std;

// Sorts arr[left], arr[left + 1], ... , arr[right - 1]
void quick_sort(int arr[], int left, int right){
    if (left + 1 >= right) return;
    int pivot = arr[left];
    int pivot_idx;          // final position of pivot in arr[] just before the recursive call
    
    int tmp[right - left];
    int tmp_idx = 0;
    
    for(int i = left + 1; i < right; i++){
        if (arr[i] <= pivot){
            tmp[tmp_idx] = arr[i];
            tmp_idx++;
        }
    }
        /*
            Insert answer to part (b)
        */
    
    pivot_idx = tmp_idx;        // DO NOT ERASE 
    tmp[tmp_idx] = pivot;       // DO NOT ERASE 
    tmp_idx++;                  // DO NOT ERASE 

    /*
        Insert answer to part (c)
        
    */

    // for(int i = right; i > left; i--){
        
    for(int i = left + 1; i < right; i++){
        if (arr[i] > pivot){
            tmp[tmp_idx] = arr[i];
            tmp_idx++;
        }
        
    }
    
    for(int i = left; i < right; i++){
        arr[i] = tmp[i - left];
    }
    
    // part (d)
    quick_sort(arr, left, pivot_idx);
    quick_sort(arr, pivot_idx + 1, right);
}

int main(){
    // int arr[] = {10, 9, 8, 7, 6, 5 ,2 , 1};
    int arr[] = {10, 9,15, 78, 20, 12, 3, 7, 6, 2 ,5 , 1};

    for(int i = 0; i < 12; i++) cout << arr[i] << " ";
    cout << endl;
    quick_sort(arr, 0, 12);

    for(int i = 0; i < 12; i++) cout << arr[i] << " ";
    
}
