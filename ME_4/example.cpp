#include<bits/stdc++.h>
using namespace std;

int scratch[5]; // for backtracking

// idx -> position where we write new valid elements
void backtrack(vector<int> &v, int idx){
    // terminating condition to avoid infinite recursive calls
    if(idx == v.size()){
       for(int i = 0; i < v.size(); i++) cout << scratch[i] << " ";
       cout << endl;
    return;
    }

    // This loop inspects every possible element for the next element
    for(int i = 0; i < v.size(); i++){
        int test_num = v[i];
        bool valid = true;

        // test for validity
        for(int j = 0;j <idx; j++){
            if (scratch[j] == test_num){
                valid = false;
                break;
            }
        }

        if(valid){
            scratch[idx] = test_num; // add a valid element
            backtrack(v, idx + 1); // fill in the rest
        }
    }
}


void generate_permutation(vector<int>& v){
    backtrack(v, 0);
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5};

    int ctr = 0;

    generate_permutation(v);
    // while(next_permutation(v.begin(), v.end())){
    //     for(auto x: v) cout << x << " ";
    //     cout << endl;
    //     ctr++;
    //
        // }

    //cout << ctr << endl;

}
