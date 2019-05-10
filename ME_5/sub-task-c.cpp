#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task C

    Given: an input file "knapsack_input.txt"
      - first line: number of items, followed by knapsack capacity
      - succeeding lines: a pair of integers; weight, followed by value

    Objective:
      - make an selection with highest total value, subject to a given capacity
      - any item may be selected an *unlimited* number of times

    Complete the following solution using dynamic programming. Note: the array of items starts at index = 0.
*/

class Item{
public:
    int weight, value;
    Item(int weight = 0, int value = 0) : weight(weight), value(value){}
};

Item a[100];
int opt_val[100][100];

void optimal_selection(int num_items, int capacity){
    // base case: no available item
    for(int i = 0; i <= capacity; i++) opt_val[0][i] = 0;

    for(int i = 1; i <= num_items; i++){
        for(int j = 0; j <= capacity; j++){
            if (a[i - 1].weight > j){
                opt_val[i][j] = opt_val[i - 1][j]; // option ignored the last item
            }
            else{
                opt_val[i][j] = max(opt_val[i - 1][j], a[i].value + opt_val[i][j - a[i].weight]);
            }
        }
    }

    cout << "optimal value: " << opt_val[num_items][capacity] << endl;   // Expected output 221

    int i = num_items, j = capacity;
    while(i != 0){
        if(opt_val[i][j] != opt_val[i - 1][j]){
            cout << "select item " << i - 1 << " with weight = " << a[i - 1].weight << " and value = " << a[i - 1].value << endl;
            i = i - 1;
            /* insert code (1 pt)*/
        }
        else{
            i = i - 1;
        }
    }
}

int main(){
    ifstream file("knapsack_input.txt");

    int num_items, capacity;
    file >> num_items >> capacity;

    for(int i = 0; i < num_items; i++){
        file >> a[i].weight >> a[i].value;
    }

    optimal_selection(num_items, capacity);
}
