#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};

    for(int i = 0; i < v.size(); i++){
	cout << v[i] << " ";
    }

    v.push_back(123);
    v.push_back(123);
    v.push_back(123);
    v.push_back(123);
    cout << endl;

    for(int i = 0; i < v.size(); i++){
	cout << v[i] << " ";
    }

    v.pop_back();
    v.pop_back();
    cout << endl;

    for(int i = 0; i < v.size(); i++){
	cout << v[i] << " ";
    }

    cout << endl;
    cout << endl;

//    while(v.size() != 0){
//        for(int i = 0; i < v.size(); i++){
//       	    cout << v[i] << " ";
//	}
//	v.pop_back();
//	cout << endl;
//    }

    sort(v.begin(), v.end());
    v.insert(v.begin(), 5);
    for(auto x : v) cout << x << endl;



}
