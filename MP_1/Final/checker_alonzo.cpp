#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
using namespace std;

// this returns a vector of unordered_set of strings that contains all the
// combinations possible inside a certain group
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

// this function checks both vectors of undordered_set of strings and checks
// if there is a similar pairing in the other one
bool pair_compare(vector<unordered_set <string> >set_a, vector<unordered_set <string> > set_b){
    for (auto pairing:set_a){ 
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

    ifstream group_1("groupings-a.txt");
    ifstream group_2("groupings-b.txt");

    vector<unordered_set <string> > set_a = set_creator(group_1);
    vector<unordered_set <string> > set_b = set_creator(group_2);

    if(pair_compare(set_a, set_b)) cout << "Valid Groupings." << endl;
}
