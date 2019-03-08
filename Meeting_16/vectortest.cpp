#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

int main(){
    vector<int> v = {101, 102, 103, 104, 105};
    
    auto it = v.begin();
    cout << *it << endl; // output: 101

    v.insert(v.begin(), 100);

    cout << *v.begin() << endl;

    for(int i = 0; i < 100000; i++){
        assert(*it == 101);
        v.push_back(0);
    }
}

