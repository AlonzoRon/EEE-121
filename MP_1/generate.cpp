#include<iostream>
#include<fstream>
#include<vector>
#include<utility> //for pair
#include<algorithm> //for random_shuffle
using namespace std;

void writer(vector<string> &list, string file_name){
    ofstream output_file(file_name);
    output_file << list.size() << "\n";

    int index = 0;
    for(int i = 0; i < list.size()/3; i++){
        string first, second, third;
        first = list[index]; index++;
        second = list[index]; index++;
        third = list[index]; index++;

        output_file << first << " " << second << " " << third << "\n";
    }
}

void update_memory(vector<pair<string, vector<string > > > &pastmems_vector,
                   vector<string> &list){

    int index = 0;
    for(int i = 0; i < list.size()/3; i++){
        string first, second, third;
        first = list[index]; index++;
        second = list[index]; index++;
        third = list[index]; index++;

        for (auto name = pastmems_vector.begin(); name != pastmems_vector.end();
             name++){

            if(name->first == first){
                name->second.push_back(second);
                name->second.push_back(third);
            }
            else if(name->first == second){
                name->second.push_back(first);
                name->second.push_back(third);
            }
            else if(name->first == third){
                name->second.push_back(first);
                name->second.push_back(second);
            }
        }
    }
}

bool inside(string x,vector<string> v){
    if (find(v.begin(), v.end(), x) != v.end()){
        return true;
    }
    return false;

}

vector<string> new_groupings(vector<pair<string, vector<string > > >
                             &pastmems_vector, vector<string> &name_pool){

    vector<string> new_group;

    for (int i = 0; i < name_pool.size()/3; i++) {
        string first, second, third;

        for (auto pairing:pastmems_vector){
            if (inside(pairing.first,new_group)){
                continue;
            }
            else {
            first = pairing.first;
            new_group.push_back(first);
            break;
            }
        }

        for(auto pairing:pastmems_vector){
            if (inside(pairing.first, new_group)) continue;

            else if (inside(pairing.first, ))


        }


    }

    }

    //for (auto pairing:pastmems_vector){
    //    for (auto person:name_pool){
    //        if (person == pairing.first) continue;
    //        else if (find(pairing.second.begin(), pairing.second.end(), person) != pairing.second.end()) continue;
    //        else if (find(new_group.begin(), new_group.end(), person) != new_group.end()) continue;
    //        else {
    //            new_group.push_back(person);
    //            break;
    //        }
    //    }
    //}

    /*
    for(auto restriction_pair:pastmems_vector){
        for (auto person:name_pool){
            if (person == restriction_pair.first) continue;

            if(find(restriction_pair.second.begin(), restriction_pair.second.end(),
               person) != restriction_pair.second.end()){

               continue;
            }

            else {
                cout << "pushed an element" << endl;
                new_group.push_back(person);
                break;
            }
            // for (auto pastmem:restriction_pair.second){
            //     if (pastmem == person) break;
            //     new_group.push_back(person);
            //     break;
            // }
        }
    }
    */

    // return new_group;

    //for(auto person:name_pool){
    //    for (auto restriction:pastmems_vector){
    //        if(person == restriction.first){
    //
    //            for (auto past_mem:restriction.second){
    //                if (person == past_mem){
    //                    continue;
    //                new_group.push_back(person);
    //                break;
    //                }
    //                }
    //            }
    //        }
    //    }
    //}





int main(){
    vector<pair<string, vector<string> > > pastmems_vector;
    pair<string, vector<string> > pastmems;
    vector <string> name_pool;

    ifstream input_file("class-list.txt");
    int n;
    input_file >> n;

    for (int i = 0; i < n; i++) {

        pair<string, vector <string> > curr_pair;

        string name;
        input_file >> name;
        curr_pair.first = name;

        pastmems_vector.push_back(curr_pair);
        name_pool.push_back(name);
    }

    random_shuffle(name_pool.begin(), name_pool.end());

    writer(name_pool, "groupings-a.txt");
    update_memory(pastmems_vector, name_pool);


    random_shuffle(name_pool.begin(), name_pool.end());
    //for (auto x:name_pool) cout << x << endl;
    vector<string> new_group = new_groupings(pastmems_vector, name_pool);

    writer(new_group, "groupings-b.txt");
    update_memory(pastmems_vector, new_group);

    for (auto x:pastmems_vector){
        cout << x.first << " past members: ";
        for(auto y:x.second) cout << y << " ";
        cout << endl;
    }
}
