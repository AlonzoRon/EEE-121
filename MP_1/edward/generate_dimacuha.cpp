#include <bits/stdc++.h>
using namespace std;

bool valid_check(vector<string> &group_a, vector<string> &group_b){

//for(auto x:group_a) cout << x << " ";
//cout << endl;

//ifstream name1, name2;
//name1.open("groupings-a.txt");
//name2.open("groupings-b.txt");

int ctr, ctr2;

ctr = group_a.size();
ctr2 = group_b.size();


vector< vector<string> > v1;

int idx = 0;
for (int i=0; i < ctr/3 ; i++){
    string a, b, c;
    vector<string> v2;

    a = group_a[idx] ; idx++; 
    b = group_a[idx] ; idx++;
    c = group_a[idx] ; idx++;

//    cout << idx << endl;
//    cout << a << b << c << endl;

    v2.push_back(a);
    v2.push_back(b);
    v2.push_back(c);
    v1.push_back(v2);
}

string p_pair[2];
int emp = 0;                            //counter for every failed pair search

int idx2 = 0;
for (int j = 0; j < int(ctr/3); j++){
    string x, y, z;

    x= group_b[idx2] ;idx2++;
    y= group_b[idx2] ;idx2++;
    z= group_b[idx2] ;idx2++;
 //   cout << x << y << z;

for (int k = 0; k < int(ctr/3); k++){
        for (int l = 0; l <=2; l++){
            if (v1[k][l] == x){
                string tmp1, tmp2;
                if (l == 0){
                    tmp1 = v1[k][l+1];
                    tmp2 = v1[k][l+2];
                }
                else if (l == 1){
                    tmp1 = v1[k][l-1];
                    tmp2 = v1[k][l+1];
                }

                if (tmp1 == y){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break; }
                else if (tmp1 == z){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == y){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == z){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else { emp += 1; break; }
            }


            else if (v1[k][l] == y){
                string tmp1, tmp2;
                if (l == 0){
                    tmp1 = v1[k][l+1];
                    tmp2 = v1[k][l+2];
                }
                else if (l == 1){
                    tmp1 = v1[k][l-1];
                    tmp2 = v1[k][l+1];
                }
                else if (l == 2){
                    tmp1 = v1[k][l-1];
                    tmp2 = v1[k][l-2];
                }
                if      (tmp1 == x){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp1 == z){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == x){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == z){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else { emp += 1; break; }
            }

            else if (v1[k][l] == z){
                string tmp1, tmp2;
                if (l == 0){
                    tmp1 = v1[k][l+1];
                    tmp2 = v1[k][l+2];
                }
                else if (l == 1){
                    tmp1 = v1[k][l-1];
                    tmp2 = v1[k][l+1];
                }
                else if (l == 2){
                    tmp1 = v1[k][l-1];
                    tmp2 = v1[k][l-2];
                }
                if      (tmp1 == y){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp1 == x){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == y){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else if (tmp2 == x){ cout << "Repeated Pair: " << x << " and " << y  << endl; return false; break;}
                else { emp += 1; break;}
            }
        }
    }
}


if (emp == int(ctr-1)) cout << "valid groupings" << endl; return true;
}

void file_write(vector <string> v, string filename){
    ofstream output(filename); 

    int idx = 0;
    output << v.size() << "\n";
    for(int i = 0; i < v.size()/3; i++){
        string a, b, c;
        a = v[idx]; idx++;
        b = v[idx]; idx++;
        c = v[idx]; idx++;

        output << a << " " << b << " " << c << "\n";
    }
}


int main(){
        
    vector<string> group1;
    vector<string> group2;
    vector<string> group3;
    vector<string> group4;
    vector<string> group5;
    vector<string> group6;
    ifstream input_file("class-list.txt");      //enter class-list.txt here


    int n;
    input_file >> n;

    for(int i = 0; i < n; i++){

    string student;
    input_file >> student;

    group1.push_back(student);
    group2.push_back(student); 
    group3.push_back(student); 
    group4.push_back(student); 
    group5.push_back(student); 
    group6.push_back(student); 

    }

//cout << "Generating groupings" << endl;
file_write(group1, "grouping-1.txt");
//cout << "Grouping 1 generated!" << endl;
    
while(!valid_check(group1, group2)){
    random_shuffle(group2.begin(), group2.end());
}

file_write(group2, "grouping-2.txt");

//cout << "Grouping 2 generated!" << endl;

while(!(valid_check(group1,group3) && valid_check(group2, group3))){
    random_shuffle(group3.begin(), group3.end());
    }

file_write(group3, "grouping-3.txt");

//cout << "Grouping 3 generated!" << endl;

while(!(valid_check(group3,group4) && valid_check(group2, group4) && valid_check(group1, group4))){
    random_shuffle(group4.begin(), group4.end());
    }

file_write(group4, "grouping-4.txt");
//cout << "Grouping 4 generated!" << endl;

while(!(valid_check(group4,group5) && valid_check(group3, group5) && valid_check(group2, group5) && valid_check(group1, group5))){
    random_shuffle(group5.begin(), group5.end());
    }

file_write(group5, "grouping-5.txt");
//cout << "Grouping 5 generated!" << endl;

while(!(valid_check(group5,group6) && valid_check(group4, group6) && valid_check(group3, group6) && valid_check(group2, group6) && valid_check(group1, group6))){
    random_shuffle(group6.begin(), group6.end());
    }

file_write(group6, "grouping-6.txt"); 
//cout << "Grouping 6 generated!" << endl;
cout << "Groups generated!" << endl; 

}
