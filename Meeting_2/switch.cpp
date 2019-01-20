#include <iostream>
using namespace std;

int main() {

	char grade;
	
	cout << "enter grade: ";
	cin >> grade;

	switch(grade){

		case 'A': cout << "Excellent" << endl; break;
		case 'C': cout << "pass" << endl; break;
		case 'E': cout << "needs improvement" << endl; break;
		case 'F': cout << "fail" << endl; break;
		default : cout << "invalid input" << endl; break;

	}
    
}
