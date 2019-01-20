#include <iostream>
using namespace std;

int g(int x, int n){
	return (x * x + 1) % n;

}

int gcd(int m, int n){

	if(m < 0){
		m = -m;
	}

	if(n < 0){
		n = -n;
	}

	if(n == 0){
		return m;
	}

	return gcd(n, m % n);
}

bool maybe_prime(int n){
	int x = 2;
	int y = 2;
	int d = 1;

	while(d == 1){
		x = g(x, n);
		y = g(g(y, n), n);
		d = gcd(x - y, n);
	}

	return d == n;

}

int main(){
	// cout << g(4, 3) << endl;
	// cout << maybe_prime(3) << endl;
	
	for(int i = 100; i <= 200; i++){
		if(maybe_prime(i) == 1){
			cout << i << endl;
		}
	}
	
}
