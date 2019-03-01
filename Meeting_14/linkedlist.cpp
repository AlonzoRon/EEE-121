#include<iostream>
#include<fstream>
#include<deque>
using namespace std;

int main(){
    
    deque<int> D;

    //  for(int i = 0; i < 1024; i++) D.push_back(i);

    //  for(int i = 0; i < D.size(); i++){
    //      cout << &D[i] << endl;
    //  }

    for(int i = 0; i < 100000; i++) D.push_back(0);
    for(int i = 0; i < 100000; i++) D.push_front(0);

}

    
