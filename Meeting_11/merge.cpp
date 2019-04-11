#include<iostream>
#include<fstream>
using namespace std;

// (recursive) invariant: left is included, right is not
// This function will sort [left, right)

void merge_sort(int arr[], int left, int right){ if(left >= right) return;
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid, right);

    // MERGE [left, mid) and [mid, right)
    int left_size = mid - left;
    int right_size = right - mid;

    int tmp[left_size + right_size]; // temporary storage for merge
    int left_ptr = left, right_ptr = mid;
    for(int i = 0; i < left_size + right_size; i++){
        if(right_ptr == right || arr[left_ptr] < arr[right_ptr]){
            tmp[i] = arr[left_ptr];
            left_ptr++;
        {
        else{
            tmp[i] = arr[right_ptr];
            right_ptr++;
        }
    }
    for (int i = left; i < right; i++){
        arr[i] = tmp[i - left];
    }
}

int main(){
    ifstream sorted_a("sorted_a.txt");
    ifstream sorted_b("sorted_b.txt");
    ofstream file_out("merged.txt");

    // int a, b, c;

    // eee121 >> a >> b >> c;
    // cout << a << " " << b << " " << c << endl;

    int L[50000], R[50000];
    int M[100000];

    // for(int i = 0; i < 50000; i++) file_a >> L[i]
    // for(int i = 0; i < 50000; i++) file_a >> L[i]

    for(int i = 0; i < 50000; i++){
        int current;
        sorted_a >> current;
        L[i] = current;
    }

    for(int i = 0; i < 50000; i++){
        int current;
        sorted_b >> current;
        R[i] = current;
    }

    // for(int i = 49500; i < 50000; i++){
    //     cout << L[i] << "\t" << R[i] << endl;
    // }

    int left = 0, right = 0;
    for(int i = 0; i < 100000; i++){
        if (right == 50000 || L[left] < R[right]){
            M[i] = L[left];
            left++;
        }
        else{
            M[i] = R[right];
            right++;
        }
    }

    // for (int i = 0; i < 20; i++) cout << M[i] << endl;
    for (int i = 0; i < 100000; i++){
        file_out << M[i] << endl;
    }
}
