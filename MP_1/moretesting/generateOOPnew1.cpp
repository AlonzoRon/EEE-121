#include<iostream>
#include<fstream>
#include<vector>
#include<utility> //for pair
#include<algorithm> //for random_shuffle
using namespace std;

class Member{
public:
    Member(string name);
    string name;
    vector<string> ex_mems;

    void print_exmems();
};

Member::Member(string name){
    this -> name = name;
}

void Member::print_exmems(){
    for (auto exmember:this->ex_mems){
        cout << exmember << " ";
    }
}

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

bool inside(string x, vector<string> v){
    if (find(v.begin(), v.end(), x) != v.end()){
        return true;
    }
    return false;
}

int find_mem(vector<Member> classlist, string name){
    int index = 0;

    for (auto x:classlist){
        if(x.name == name) return index;
        index++;
    }
    return 0;
}

vector<string> new_groupings(vector<Member> &classlist, vector<string> &name_pool){
    vector<string> new_group;

    for (int i = 0; i < name_pool.size()/3; i++){

        string first, second, third;
        vector<string> current_grouping;

        for(auto person:name_pool){
            if (inside(person, new_group)){
                continue;
            }
            else{
                first = person;
                new_group.push_back(first);
                //cout << "pushed" << first << endl;
                break;
            }
        }

        int loc_mem1 = find_mem(classlist, first);

        for(auto person:name_pool){
            int loc_currmem = find_mem(classlist, person);
            if (inside(person, new_group)){
                continue;
            }
            else if(inside(person, classlist[loc_mem1].ex_mems)){
                continue;
            }
            else if(inside(person, classlist[loc_currmem].ex_mems)){
                continue;
            }
            else{
                second = person;
                new_group.push_back(second);
                //cout << "pushed" << second << endl;
                break;
            }
        }

        int loc_mem2 = find_mem(classlist, second);

        for(auto person:name_pool){
            int loc_currmem = find_mem(classlist, person);
            if (inside(person, new_group)){
                continue;
            }
            else if (inside(person, classlist[loc_mem1].ex_mems) || inside(person, classlist[loc_mem2].ex_mems)){
                continue;
            }
            else if(inside(person, classlist[loc_currmem].ex_mems)){
                continue;
            }
            else{
                third = person;
                new_group.push_back(third);
                //cout << "pushed" << third << endl;
                break;
            }
        }
    }


//
//
//            }
//            if(inside(member.name, classlist[loc_mem1].ex_mems)){
//                continue;
//            }
//            else if(inside(member.name, new_group)){
//                continue;
//            }
//            else{
//                second = member.name;
//                new_group.push_back(second);
//                break;
//            }
//        }
//
//        int loc_mem2 = find_mem(classlist, second);
//
//        for (auto member:classlist){
//            if(inside(member.name, classlist[loc_mem1].ex_mems) ||
//               inside(member.name, classlist[loc_mem2].ex_mems)){
//                continue;
//            }
//            else if(inside(member.name, new_group)){
//                continue;
//            }
//            else{
//                third = member.name;
//                new_group.push_back(third);
//                break;
//            }
//        }
//
//        }
//            //for(auto restriction:classlist[loc_mem1].ex_mems){
//            //    if(inside(member.name, restriction))
    return new_group;
}







//        for(auto member:classlist){
//            if(inside(member.name), new_group){
//                continue;
//            }
//            else{
//                if (inside(member.name, ))
//            }
//        }
//
//    }

int main(){
    vector<Member> classlist;
    vector<string> name_pool;

    ifstream input_file("class-list.txt");
    int n;
    input_file >> n;

    for (int i = 0; i < n; i++){
        string name;
        input_file >> name;

        classlist.push_back(Member(name));
        name_pool.push_back(name);
    }

    writer(name_pool, "1");
    update_memory(classlist, name_pool);


    //random_shuffle(name_pool.begin(), name_pool.end());

    //for (auto x:name_pool) cout << x << endl;



    for (int i = 2; i < 7; i++){
        string filename = to_string(i);

        random_shuffle(name_pool.begin(), name_pool.end());
        vector<string> new_group = new_groupings(classlist, name_pool);
        cout << name_pool.size() << endl;

        //while (new_group.size() < name_pool.size()){
        //    random_shuffle(name_pool.begin(), name_pool.end());
        //    vector<string> new_group = new_groupings(classlist, name_pool);
        //    //cout << "name pool size"<< name_pool.size()<< endl;;
        //    //cout << new_group.size()<< endl;
        //}

        writer(new_group, filename);
        update_memory(classlist, new_group);

    }

    //update_memory(classlist, new_group);

    for(auto member:classlist){
        cout << member.name << " Ex-mems: ";
        member.print_exmems();
        cout << endl;
    }

    cout << find_mem(classlist, "Raynor") << endl;

}
