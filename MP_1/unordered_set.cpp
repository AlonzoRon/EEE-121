#include<iostream>
#include<unordered_set>
using namespace std;

int main(){
    unordered_set<string> x;
    unordered_set<string> y;

    x.insert("Juan");
    x.insert("Allen");

    y.insert("Allen");
    y.insert("marco");

    if (x == y){
        cout << "they are the same!" << endl;
    }
    else cout << "not the same!" << endl;
}
