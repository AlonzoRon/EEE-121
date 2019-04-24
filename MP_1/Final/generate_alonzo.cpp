#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm> //for random_shuffle
using namespace std;

// simple Member class to avoid using nested data structures
class Member{
public:
    Member(string name);
    string name;
    vector<string> ex_mems; // this is the database of ex-members of each person

    void print_exmems();
};

Member::Member(string name){
    this -> name = name;
}

// printing of ex members used for debugging
void Member::print_exmems(){
    for (auto exmember:this->ex_mems){
        cout << exmember << " ";
    }
}

// this function writes the output file groupings-x.txt in the desired format
// it accepts a vector of strings wherein every 3 members is a group
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

// this function is used to update the "memory/database" of past members
// by accessing the database, we can make sure that no member is repeated
void update_memory(vector<Member> &classlist, vector<string> &groupings){
    int index = 0;
    for(int i = 0; i < groupings.size()/3; i++){
        string first, second, third;
        first = groupings[index]; index++;
        second = groupings[index]; index++;
        third = groupings[index]; index++;

        for (auto member = classlist.begin(); member!= classlist.end(); member++){
            if (member->name == first){
                member->ex_mems.push_back(second);
                member->ex_mems.push_back(third);
            }
            else if (member->name == second){
                member->ex_mems.push_back(first);
                member->ex_mems.push_back(third);
            }
            else if (member->name == third){
                member->ex_mems.push_back(first);
                member->ex_mems.push_back(second);
            }
        }
    }
}

// this function created to mimic the 'if x in y' boolean statement in Python
// it checks if certain string x is inside a certain vector of strings
bool inside(string x, vector<string> v){
    if (find(v.begin(), v.end(), x) != v.end()){
        return true;
    }
    return false;
}

// returns the index of a certain member from the main classlist
int find_mem(vector<Member> classlist, string name){
    int index = 0;

    for (auto x:classlist){
        if(x.name == name) return index;
        index++;
    }
    return 0;
}

// this function selects groupings which have no repeating members
// it traverses the name_pool vector of strings and chooses members
vector<string> new_groupings(vector<Member> &classlist, vector<string> &name_pool){
    vector<string> new_group;

    for (int i = 0; i < name_pool.size()/3; i++){

        string first, second, third;

        for(auto person:name_pool){
            if (inside(person, new_group)){     // if already in the new group
                continue;
            }
            else{
                first = person;
                new_group.push_back(first);
                break;
            }
        }

        int loc_mem1 = find_mem(classlist, first);

        for(auto person:name_pool){
            if (inside(person, new_group)){     // if already in the new group
                continue;
            }
            else if(inside(person, classlist[loc_mem1].ex_mems)){
                continue;  // this checks the ex_mems of group member 1
            }
            else{
                second = person;
                new_group.push_back(second);
                break;
            }
        }

        int loc_mem2 = find_mem(classlist, second);

        for(auto person:name_pool){
            if (inside(person, new_group)){     // if already in the new group
                continue;
            }
            else if (inside(person, classlist[loc_mem1].ex_mems) ||
                     inside(person, classlist[loc_mem2].ex_mems)){
                continue; // this checks the ex_mems of both group member 1 & 2
            }
            else{
                third = person;
                new_group.push_back(third);
                break;
            }
        }
    }

    // in some cases, the newly formed group is lacking in size (meaning it
    // traversed new_pool in a way that the final grouping has repeating members)
    // with that, we shuffle the name_pool and try again using a recursive call
    if (new_group.size() < name_pool.size()){
            random_shuffle(name_pool.begin(),name_pool.end());
            return new_groupings(classlist, name_pool);
    }

    // when you get here, meaning a complete and valid grouping has been created
    return new_group;
}

int main(){
    vector<Member> classlist;
    vector<string> name_pool;

    ifstream input_file("class-list.txt");
    int n;
    input_file >> n;

    // for loop adds students to the classlist and the name_pool
    for (int i = 0; i < n; i++){
        string name;
        input_file >> name;

        classlist.push_back(Member(name));
        name_pool.push_back(name);
    }
    // There are 3 main steps that were implemented:
    // 1 - create valid grouping (new_groupings function)
    // 2 - write valid grouping to file (writer function)
    // 3 - update the database of ex-members  (update_memory function)

    // do everything 6 times
    for (int i = 1; i <= 6; i++){
        string number = to_string(i);
        string filename = "groupings-" + number + ".txt";

        // random_shuffle for good measure
        random_shuffle(name_pool.begin(), name_pool.end());

        vector<string> new_group = new_groupings(classlist, name_pool); // step 1
        writer(new_group, filename);                                    // step 2
        update_memory(classlist, new_group);                            // step 3

    }
}
