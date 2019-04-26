#include<bits/stdc++.h>
using namespace std;

int scratch[3];

void backtrack(vector<string> &v, int num_select, int idx){
    if (idx == num_select){
        for(int i = 0; i < num_select; i++) cout << v[scratch[i]] << " ";
        cout << endl;
        return; //do not forget
    }

    int prev;
    if (idx == 0) prev = -1;
    else prev = scratch[idx - 1];

    for(int i = prev + 1; i < v.size(); i++){
        scratch[idx] = i;
        backtrack(v, num_select, idx + 1);

    }

}
void generate_subset(vector<string> &v, int num_select){
    backtrack(v, num_select, 0);

}

int main(){
    vector<string> v = {"a", "b", "c", "d", "e"};

    generate_subset(v, 3);
}
