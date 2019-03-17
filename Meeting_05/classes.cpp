#include<iostream>
using namespace std;

// class class_name {
//     type_a member_a;
//     type_b member_b;
//     // and so on.
// }

// in c++, members are private by default

class Pair {
public:
    int first = 10;
    int second = 20;

    Pair(int a, int b){ // this is the constructor
        first = a;
        second = b;
        cout << "You just created a pair" << endl;
    }

    void swap(){
        int temp;
        temp = first;
        first = second;
        second = temp;
    }
    
    void print(){
        cout << "(" << first << ", " << second << ")" << endl;
    }

};


int main(){
    Pair p(1, 2); // created a Pair object named p 

    // cout << p.first << endl;
    // cout << p.second << endl;

    p.print();
    p.swap();
    p.print();

    // cout << p.first << endl;
    // cout << p.second << endl;
    
}
