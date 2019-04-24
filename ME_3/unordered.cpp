#include<unordered_map>
#include<iostream>
using namespace std;

int main(){
    unordered_map<string, int> H;

    H["fish"] = 10;

    cout << H["fish"] << endl;

}
