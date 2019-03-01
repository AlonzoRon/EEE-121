#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main(){
    vector<int> v;
    
    ofstream csv_file("vector_mem.csv");
    csv_file << "i,v.size(),v.capacity()" << endl;

    for(int i = 1;i <= 100000; i++){
        csv_file << i << "," << v.size() << "," << v.capacity() << endl;
        v.push_back(i);
    }

    
}

    
