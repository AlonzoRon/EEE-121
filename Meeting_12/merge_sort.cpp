#include<iostream>
#include<fstream>
using namespace std;

// (recursive) invariant: left is included, right is not
// This function will sort [left, right) 
void merge_sort(int arr[], int left, int right){
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
    int arr[100000];
    
    ifstream file("unsorted_large.txt");
    ofstream sorted_file("sorted_large.txt");
    
    for(int i = 0; i < 100000; i++) file >> arr[i];
    
    merge_sort(arr, 0, 100000);
    
    for(int i = 0; i < 100000; i++) sorted_file << arr[i] << endl;
}