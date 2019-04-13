#include<iostream>
#include<fstream>
#include<vector>
#include<utility> //for pair
#include<algorithm> //for random_shuffle
using namespace std;

void push_vector(vector<pair<string, vector <string> > >  &v){
    pair<string, vector<string> > P;
    P.first = "Ron";
    P.second.push_back("I like trains") ;
    v.push_back(P);
}

int main(){
    vector<pair<string, vector <string> > > v;

    push_vector(v);
    push_vector(v);
    push_vector(v);
    push_vector(v);

    for (auto x: v){
        cout << x.first << " ";
        for (auto y:x) cout << y << endl;
    }

}
