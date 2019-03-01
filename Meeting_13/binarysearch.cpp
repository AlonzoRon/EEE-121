#include<iostream>
#include<algorithm>
using namespace std;

int main(){

    int arr[] = {4, 2, 1, -3, -6, 5, 7, 8};
    
    sort(arr, arr + 8);

    if (binary_search(arr, arr + 8, 5)) cout << "found" << endl;
    else cout << "not found" << endl;

}
