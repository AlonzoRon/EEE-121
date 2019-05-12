#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task A

    Given: an input file "knapsack_input.txt"
      - first line: number of items, followed by knapsack capacity
      - succeeding lines: a pair of integers; weight, followed by value

    Objective:
      - make an selection with highest total value, subject to a given capacity
      - any item may be selected an *unlimited* number of times

    Implement the following greedy strategy:
      - Select an item with the lowest weight
      - Fill the knapsack with the chosen item as much as possible
      - Output the total value obtained using this method

    Expected output: 204
*/

class Item{
public:
    int weight, value;
    Item(int weight = 0, int value = 0) : weight(weight), value(value){}
};

int main(){
    ifstream file("knapsack_input.txt");

    int num_items, capacity;
    file >> num_items >> capacity;

    Item a[num_items];

    for(int i = 0; i < num_items; i++){
        file >> a[i].weight >> a[i].value;
    }

    int min_weight = a[0].weight;
    for(auto item: a){
        if (item.weight <= min_weight) min_weight = item.weight;
    }

    int burden = 0;
    int total_value = 0;
    for(auto item : a){
        if (item.weight == min_weight){
            while(burden <= capacity){
                burden += item.weight;
                if(burden <= capacity){
                    total_value += item.value;
                }
            }
            break;
        }
    }

    // int total_value = (capacity / a[])

    cout << total_value << endl;


    /*
        Insert code here implementing the greedy strategy.
    */
}
