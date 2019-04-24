#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){
    vector <pair <string, vector <string> > > past_memsvector;
    pair <string, vector<string> > past_mems;
    ifstream class_list("class-list.txt");
    int n;
    class_list >> n;

    cout << n << endl;

    //for(int i = 0; i < n; i++){
    //    string person;
    //    cout << person << endl;
    //    class_list >> person;
//
    //    pair <string, vector <string> >  curr_pair;
//
    //    curr_pair.first = person;
//
    //    past_memsvector.push_back(curr_pair);
    //}
}
