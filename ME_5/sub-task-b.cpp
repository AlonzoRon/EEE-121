#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task B

    Given: an input file "knapsack_input.txt"
      - first line: number of items, followed by knapsack capacity
      - succeeding lines: a pair of integers; weight, followed by value

    Objective:
      - make an selection with highest total value, subject to a given capacity
      - any item may be selected an *unlimited* number of times

    Complete the following solution using exhaustive search via recursive backtracking.

    Expected output: 221
*/

class Item{
public:
    int weight, value;
    Item(int weight = 0, int value = 0) : weight(weight), value(value){}
};

Item a[100];

int freq[100];
int max_val;

void backtrack(int num_items, int capacity, int idx){
    if (idx == num_items){
        int total_weight = 0, total_value = 0;

        for(int i = 0; i < num_items; i++){
            total_value += freq[i] * a[i].value;
            total_weight += freq[i] * a[i].weight;
        }

        if (total_weight <= capacity && total_value > max_val){
            max_val = total_value;
        }

        return;
    }

    // i * a[idx].weight <= capacity

    for(int i = 0;i <= capacity/a[idx].weight; i++){
        freq[idx] = i;
        backtrack(num_items, capacity, idx + 1);
    }
}

void optimal_selection(int num_items, int capacity){
    max_val = 0;
    backtrack(num_items, capacity, 0);
}

int main(){
    ifstream file("knapsack_input.txt");

    int num_items, capacity;
    file >> num_items >> capacity;

    for(int i = 0; i < num_items; i++){
        file >> a[i].weight >> a[i].value;
    }

    optimal_selection(num_items, capacity);

    cout << "optimal value: " << max_val << endl;
}
