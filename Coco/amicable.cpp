#include <iostream>
using namespace std;

int sum_divisors(int number){
    int sum = 0;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) sum += i;
    }
    return sum;
}

bool is_amicable(int number){
    if (sum_divisors(sum_divisors(number)) == number) return true;
    else return false;
}

int main(){
    cout << sum_divisors(10) << endl;
    cout << is_amicable(284) << endl << endl << endl;

    cout << sum_divisors(496) << endl << endl;

    int sum = 0;
    for (int i = 1; i <= 10000; i++) {
        if (is_amicable(i)) {
            cout << i << endl;
            sum += i;
        }
    }
    cout << endl << "sum: " << sum << endl;

}
