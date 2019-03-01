#include<iostream>
#include<fstream>
using namespace std;

int total_effort = 0;

// (recursive) invariant: left is included, right is not
// This function will sort [left, right) 
void merge_sort(int arr[], int left, int right){
    total_effort += right - left;
    
    if (left + 1 >= right) return;
    
    int mid = (left + right)/2;
    
    merge_sort(arr, left, mid);
    merge_sort(arr, mid, right);
    
    // MERGE [left, mid) and [mid, right)
    int left_size = mid - left;
    int right_size = right - mid;
    int tmp[left_size + right_size];    // temporary storage for merge
    
    int left_ptr = left, right_ptr = mid;
    for(int i = 0; i < left_size + right_size; i++){
        if (right_ptr == right || (left_ptr < mid && arr[left_ptr] < arr[right_ptr])){
            tmp[i] = arr[left_ptr];
            left_ptr++;
        }
        else{
            tmp[i] = arr[right_ptr];
            right_ptr++;
        }
    }
    
    for(int i = left; i < right; i++){
        arr[i] = tmp[i - left];
    }
}


int main(){
    ifstream file("permutations_large.txt");
    ofstream log_file("mergesort_runtime.out");
    
    int arr[8];
    for(int it = 0; it < 40320; it++){
        for(int i = 0; i < 8; i++) file >> arr[i];
        
        int tmp[8];
        for(int i = 0; i < 8; i++) tmp[i] = arr[i];
        
        total_effort = 0;
        merge_sort(arr, 0, 8);
        log_file << total_effort << endl;
        
        if (total_effort == 41){
            for(int i = 0; i < 8; i++) cout << tmp[i] << " ";
            cout << endl;
            break;
        }
    }
}