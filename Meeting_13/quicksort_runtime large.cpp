#include<bits/stdc++.h>
using namespace std;

int total_effort;

// Sorts arr[left], arr[left + 1], ... , arr[right - 1]
void quick_sort(int arr[], int left, int right){
    total_effort += right - left;
    
    if (left + 1 >= right) return;
    
    int pivot = arr[left];
    int pivot_idx;
    
    int tmp[right - left];
    int tmp_idx = 0;
    
    for(int i = left + 1; i < right; i++){
        if (arr[i] <= pivot){
            tmp[tmp_idx] = arr[i];
            tmp_idx++;
        }
    }
    
    pivot_idx = tmp_idx;
    tmp[tmp_idx] = pivot;
    tmp_idx++;
    
    for(int i = left + 1; i < right; i++){
        if (arr[i] > pivot){
            tmp[tmp_idx] = arr[i];
            tmp_idx++;
        }
    }
    
    for(int i = left; i < right; i++){
        arr[i] = tmp[i - left];
    }
    
    quick_sort(arr, left, left + pivot_idx);
    quick_sort(arr, left + pivot_idx + 1, right);
}

int main(){
    ifstream file("unsorted_large.txt");
    ofstream log_file("unsorted_largecount.out");

    int arr[100000];
    for(int i = 0; i < 100000; i++) file >> arr[i];

    int tmp[100000];
    for(int i = 0; i < 100000; i++) arr[i] = tmp[i];

    quick_sort(arr, 0, 100000);
    cout << total_effort << endl;
    

    
   // int arr[8];
   // 
   // for(int it = 0; it < 40320; it++){ //read from
   //     for(int i = 0; i < 8; i++) file >> arr[i];
   //     
   //     int tmp[8]; //duplicate
   //     for(int i = 0; i < 8; i++) tmp[i] = arr[i];
   //     
   //     total_effort = 0; //reset total effort
   //     quick_sort(arr, 0, 8); //sort
   //     log_file << total_effort << endl; //report in log file
   //     
//        if (total_effort == 24){
//            for(int i = 0; i < 8; i++) cout << tmp[i] << " ";
//            cout << endl;
//            break;
//        }
    }
}

// 4, 2, 1, 3, 6, 5, 7, 8
// 2, 1, 4, 3, 6, 5, 7, 8
