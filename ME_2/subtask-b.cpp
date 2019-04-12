#include<bits/stdc++.h>
using namespace std;

/*
    SUBTASK B: (3 pts) Complete the comparator function for custom sorting of a Point object
     - custom_sort -> should sort Points according to increasing x, then by decreasing y
*/

class Point{
public:
    int x, y;
    Point(int x, int y) : x(x), y(y){};
};

bool custom_sort(const Point& a, const Point& b){
    //return a.x < b.x && a.y > b.y;

    //bool cond_1 = a.x < b.x;
    //bool cond_2 = a.y > b.y;

    //return cond_1 && cond_2;

    //if ((a.x < b.x) && (a.y > b.y)) return true;
    /*
        Complete the function.
    */
    if (a.x == b.x){
        return a.y > b.y;
    }
    else return a.x < b.x;
}

ostream& operator<<(ostream& os, const Point& P){
    os << "(" << P.x << ", "<< P.y << ")";
    return os;
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
    vector<Point> v = {{5,2}, {4,3}, {3,3}, {4,6}, {1,4}, {1,7}, {5,5}, {1,3}};

    sort(v.begin(), v.end(), custom_sort);

    cout << "using custom_sort: " << endl;
    cout << v << endl;
    // ^ Expected output: [(1, 7), (1, 4), (1, 3), (3, 3), (4, 6), (4, 3), (5, 5), (5, 2)]
}
