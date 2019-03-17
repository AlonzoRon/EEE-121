#include<iostream>
#include<set>
using namespace std;

int main(){
    set<string> S = {"the", "the", "the", "quick", "brown", "fox"};

    /* 
        S.insert(val);
        S.erase(val);
        S.size();
        S.empty();
        S.begin();
        S.end();
        it--;
    */ 

    S.erase("the");
    for(auto x:S) cout << x << " ";
    

}
