#include <iostream>
#include <ctime>
using namespace std;

void f(string s){
    cout << "done" << endl;
}

int main(){
    time_t start = time(NULL);

    string s = "simple string";

    for(int i = 0; i < 27; i++){
        s += s;
    }

    cout << "done" << endl;
    cout << start << endl;
}
