#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> V;

    for (size_t i = 15; i > 10; i--) {
        V.push_back(i);
    }

    for(auto x : V) cout << x << " ";
    // [10, 11, 12, 13, 14]

    cout << endl;
    cout << *(V.begin()) << endl;
    cout << *(V.end() - 1) << endl;

    // .begin() and .end() are pointers.
    // .begin() points to the first element
    // .end() points to the last element + 1

    cout << V.size() << endl;

    // .size() returns number of elements

    // .pop_back() deletes last element

    sort(V.begin(), V.end());

    for(auto x : V) cout << x << " ";
}
