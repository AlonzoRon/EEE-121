#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

int main(){
    ifstream file("unsorted_large.txt");   
    ofstream out("output.txt");
    int arr[100000];
    for(int i = 0; i < 100000; i++) file >> arr[i];

    sort(arr, arr + 100000);

    
    for(int i = 0; i < 100000; i++) arr[i] <<  out << endl;

    
}
