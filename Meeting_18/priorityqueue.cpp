#include<iostream>
#include<queue>
#include<list>
using namespace std;

int main(){
    priority_queue<int, vector<int>, greater<int>> PQ;
    list<int> ls = {7, 4, 5, 1, 9, 10};

    for(auto x:ls) PQ.push(x);

    cout << PQ.top() << endl;
}
