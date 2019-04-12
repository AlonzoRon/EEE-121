#include<bits/stdc++.h>
using namespace std;

/*
    SUBTASK A: (3 pts) Complete the comparator functions for custom sorting of ints
     - decreasing_int -> should sort integers from highest to lowest
     - by_absval      -> should sort integers by increasing absolute values
*/

bool decreasing_int(const int& a, const int& b){
    return b < a;
    /*
        Complete the function.
    */
}

bool by_absval(const int& a, const int& b){
    return abs(a) < abs(b);
    /*
        Complete the function.
    */
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v){
    bool flag = false;
    os << "[";
    for(auto x : v){
        if (flag) os << ", ";

        flag = true;
        os << x;
    }
    os << "]";
    return os;
}

int main(){
    vector<int> v = {-6, -9, 7, -5, 0, 1, -2, 9, 6, 2, 4, 5};

    sort(v.begin(), v.end(), decreasing_int);

    cout << "sorted using decreasing_int: " << v << endl;
    // ^ Expected output: [9, 7, 6, 5, 4, 2, 1, 0, -2, -5, -6, -9]

    sort(v.begin(), v.end(), by_absval);

    cout << "sorted using by_absval: " << v << endl;
    // ^ Possible output: [0, 1, 2, -2, 4, 5, -5, 6, -6, 7, 9, -9]
}
