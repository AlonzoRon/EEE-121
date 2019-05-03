#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task B

    Use recursive backtracking to enumerate all possible paths
    that start at stage[0] and end at stage[3].

    Use the format: <first_vertex> -> <second_vertex> -> ... -> <last_vertex>

    Example paths:
     - A -> C -> G -> J
     - B -> D -> F -> I
*/

string vertex[10];               // for backtracking

void print_path(int num_stages){
    cout << "[";
    for(int i = 0; i < num_stages; i++){
        if (i) cout << ", ";
        cout << vertex[i];
    }
    cout << "]" << endl;
}

void backtrack(vector<string> stage[], int idx, int num_stages){
    if (idx == num_stages){
        print_path(num_stages);
        return;
    }

    // Try all possible vertices to be written to vertex[idx]

    for(auto v : stage[idx]){
        vertex[idx] = v;
        backtrack(stage, idx + 1, num_stages);
    }


    //for(int i = idx; i < num_stages; i++){
    //    for(int j = 0; j < stage[i].size(); j++){
    //
    //    }
    //}

//    for (int i = idx; i < num_stages; i++){
//        bool valid = false;
//        string test_string;
//
//        for(int j = 0; j < stage[i].size(); j++){
//            test_string = stage[i][j];
//            if (stage[i][j] != vertex[idx]){
//                //cout << stage[i][j] <<  " vs " << vertex[idx] << endl;
//                valid = true;
//                break;
//            }
//        }
//        if(valid){
//            vertex[idx] = test_string;
//            backtrack(stage, idx + 1, num_stages);
//        }
//    }

    //for (int i = 0; i < num_stages; i++){
    //    int count
    //    for(auto x:stage[i]){
//
    //    }
    //}



    /*
        Insert code here.
    */
}

void enumerate_path(vector<string> stage[], int num_stages){
    backtrack(stage, 0, num_stages);
}

int main(){
    vector<string> stage[4];

    stage[0] = {"A", "B"};
    stage[1] = {"C", "D", "E"};
    stage[2] = {"F", "G", "H"};
    stage[3] = {"I", "J"};

    enumerate_path(stage, 4);


}
