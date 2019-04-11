#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;

int main(){
    deque<int> D;

    for (size_t i = 0; i < 5; i++) {
         D.push_back(i);
    }


    for (size_t i = 10; i < 15; i++) {
        D.push_front(i);
    }

    for(auto x:D){
        cout << x << " ";
    }

    cout << endl;
    sort(D.begin(), D.end());

    for(auto x:D){
        cout << x << " ";
    }
}
