#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include<array>
#include<list>
#include<queue>
using namespace std;

int main(){
    
    queue<char> Q;

    Q.push('X');
    Q.push('K');
    Q.push('C');
    Q.push('D');

    cout << Q.front() << endl;
    Q.pop();
    cout << Q.front() << endl;

    // for(auto x : Q){
    //     cout << x << endl;
    // }

    while(!Q.empty() /* Q is not empty */){
        char x = Q.front();
        cout << x << " ";
        Q.pop();
    
    }
}

