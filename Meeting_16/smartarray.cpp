#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include<array>
#include<list>
using namespace std;

int main(){
    
    array<string, 3> arr = {"white", "board", "marker"};

    for(auto x : arr) cout << x << endl;

    array<int, 10> arr2 = {23,12,32,54,75,23,65,34,12,54};

    sort(arr2.begin(), arr2.end());

    for(auto x : arr2) cout << x << endl;
}

