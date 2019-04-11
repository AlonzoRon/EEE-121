#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main(){
    list<int> L;

    for(int i = 0; i < 10; i++){
        L.push_front(i);
    }

    for(auto x:L) cout << x << " ";
    cout << endl;

    //sort(L.begin(), L.end());

    for(auto x:L) cout << x << " ";
    cout << endl;

}
