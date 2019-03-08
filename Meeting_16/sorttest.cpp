#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include<list>
using namespace std;

int main(){
    list<int> ls = {20, 11, 18, 4, 7};

    ls.sort();

    // sort(ls.begin(), ls.end());

    for(auto x: ls) cout << x << " ";
    cout << endl;
    
}

