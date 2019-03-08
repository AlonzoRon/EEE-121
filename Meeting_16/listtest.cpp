#include<deque>
#include<forward_list>
#include<iostream>
#include<vector>
#include<list>
using namespace std;

// g++ code.cpp -stdc++11

int main(){
    list<string> S = {"white", "board", "marker", "yeah"};

    // list<string::iterator iter;
    
    auto iter = S.begin();

    // cout << *iter << endl;
    // iter++;
    // cout << *iter << endl;
    // iter++;
    // cout << *iter << endl;

    // for(int i = 0; i < S.size(); i++){
    //     cout << *iter << endl;
    //     iter++;
    // }

    // cout << endl;

    // for(auto it = S.begin(); it != S.end(); it++){
    //     cout << *it << endl;
    // }

    auto it = S.begin();
    it++;
    it++;
    it--;
}
