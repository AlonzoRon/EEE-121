#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
using namespace std;

vector<unordered_set <string> > set_creator(ifstream &input_file){
    vector<unordered_set <string> > return_set;
    int n;
    input_file >> n;

    for(int i = 0; i < n/3 ; i++){
        string first, second, third;
        input_file >> first >> second >> third;

        unordered_set<string> combination_a = {first, second};
        unordered_set<string> combination_b = {first, third};
        unordered_set<string> combination_c = {second, third};

        return_set.push_back(combination_a);
        return_set.push_back(combination_b);
        return_set.push_back(combination_c);
    }
    return return_set;
}

bool pair_compare(vector<unordered_set <string> >set_a, vector<unordered_set <string> > set_b){
    for (auto pairing:set_a){ // note: this part may need some optimization as this is O(n^2)
            for (auto other_pairing:set_b){
                if (pairing == other_pairing){
                    auto it = pairing.begin();
                    cout << "Repeated pair: "  << *it << " and " <<  *(it++) << endl;
                    return false;
                }
            }
        }
    return true;
}

int main(){

    ifstream group_1("groupings-3.txt");
    ifstream group_2("groupings-5.txt");

    vector<unordered_set <string> > set_a = set_creator(group_1);
    vector<unordered_set <string> > set_b = set_creator(group_2);

    if(pair_compare(set_a, set_b)) cout << "Valid Groupings." << endl;
}
