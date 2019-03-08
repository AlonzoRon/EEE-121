#include<iostream>
#include<cassert>
#include<vector>
#include<list>
using namespace std;

int main(){
    list<int> ls = {101, 102, 103, 104, 105};
    
    auto it = ls.begin();
    it++; it++;

    // ls.insert(iterator, value to insert);
    // for(auto x: ls) cout " " << x;

    ls.insert(it, 500);

    for(auto it = ls.begin(); it != ls.end(); it++){
        cout << *it << endl;
    }

    ls.erase(it);
    cout << endl;
    for(auto it = ls.begin(); it != ls.end(); it++){
        cout << *it << endl;
    }
    
}

