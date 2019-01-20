#include<iostream>
using namespace std;

int main(){
    // string x;
    // x = "adrian";
    // x = 49;

    string name, surname;
    int age;
    float weight;

    cout << "Enter full name (2 words only):" << endl;
    cin >> name >> surname;

    cout << "Enter age:" << endl;
    cin >> age;

    cout << "Enter weight:" << endl;
    cin >> weight;

    cout << "Hello " << name << " " << surname << endl;
    cout << "You are " << age << " years old" << endl;
    cout << "You are " << weight << " kilograms" << endl;
    cout << "You are " << weight * 2.204 << " pounds" << endl;
    cout << "Hello again" << endl;
}
