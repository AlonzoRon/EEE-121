#include<iostream>
using namespace std;

int main(){
    int ctr = 10;
    int i = 0;

    while (ctr > 0){
        cout << ctr << endl;
        ctr = ctr - 1;
    }
    
    cout << "Boom!" << endl;

    for (i; i < 10; i++) {
        cout << "Hello world " << i <<endl;
    }
    
    cout << i << endl;
}
