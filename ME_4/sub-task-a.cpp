#include<bits/stdc++.h>
using namespace std;

//void printer_forloop
/*
    Use nested for-loops to enumerate all possible paths
    that start at stage[0] and end at stage[2].

    Use the format: <first_vertex> -> <second_vertex> -> ... -> <last_vertex>

    Example paths:
     - A -> C -> G
     - B -> D -> F
*/

int main(){
    vector<string> stage[3];

    stage[0] = {"A", "B"};
    stage[1] = {"C", "D", "E"};
    stage[2] = {"F", "G"};

    for (auto x: stage[0]){
        for (auto y: stage[1]){
            for (auto z: stage[2]){
                cout << x << " -> " << y << " -> "<< z;
                cout << endl;
            }
        }
    }


}
