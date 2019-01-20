#include<iostream>
using namespace std;

int main() {

    int age;

    cout << "Insert your age: ";
    cin >> age;

    if (age < 13){
        cout << "You are a kid" << endl;
    }

    else if (age < 18){
        cout << "You are a minor" << endl;
    }

    else{
        cout << "You are an adult" << endl;
    }
}
