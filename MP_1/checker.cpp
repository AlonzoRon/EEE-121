#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(){

    ifstream group_1("groupings-1.txt");
    int n;
    vector<vector<string> > group_a;
    // ifstream group_2("groupings-2.txt");
    group_1 >> n;
    // cout << n;

    for (size_t i = 0; i < (n / 3); i++) {

        vector<string> grouping;

        string first;
        string second;
        string third;

        group_1 >> first >> second >> third;

        grouping.push_back(first);
        grouping.push_back(second);
        grouping.push_back(third);

        group_a.push_back(grouping);

        // cout << third << endl;
        // cout << second << endl;
        // cout << first << endl << endl;

    }

    for(auto grouping : group_a){
        cout << "new group------------------" << endl;
        for(auto member: grouping){
            cout << member << endl;
        }
    }
}
