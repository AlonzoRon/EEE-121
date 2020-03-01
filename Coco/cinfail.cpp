#include <iostream>
using namespace std;

int prompt(){
    int n;
    cout << "Insert a two digit number: ";
    cin >> n;

    return n;
}

int main(){

    int n = prompt();

    while (cin.fail()){
        cin.clear();
        cin.ignore(132, '\n');
        n = prompt();
    }

    // while (cin.fail()){
    //     cout << "invalid" << endl;
    //     cout << "Insert a two digit number: " << endl;
    //     cin.clear();
    //     cin >> n;
    //     if (!cin.fail()){
    //         break;
    //     }
    // }
}
