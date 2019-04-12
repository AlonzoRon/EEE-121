#include<bits/stdc++.h>
using namespace std;

/*
    SUBTASK C: (4 pts) Complete the comparator function for use in priority_queue
     -> Complete the sort_pointer code so that nodes with lowest freq are popped first.
     -> Complete the while-loop in the main function.
*/

class TreeNode{
public:
    char symbol;
    int freq;
    TreeNode *left = nullptr, *right = nullptr;

    TreeNode(char s, int f) : symbol(s), freq(f){}
};

class sort_pointer{
public:
    bool operator()(const TreeNode *a, const TreeNode *b){
        return a->freq > b->freq;
    }
};

ostream& operator<<(ostream& os, const TreeNode& t){
    os << "(" << t.symbol << ", " << t.freq << ")";
    return os;
}

int main(){
    char c[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int  f[] = {6, 7, 15, 4, 8, 5};

    priority_queue<TreeNode*, vector<TreeNode*>, sort_pointer> PQ;

    for(int i = 0; i < 6; i++){
        PQ.push(new TreeNode(c[i], f[i]));
    }

    while(PQ.size() > 1){
        TreeNode *A = PQ.top(); PQ.pop();
        TreeNode *B = PQ.top(); PQ.pop();

        cout << "popped " << *A << " and " << *B << endl;


        /*
            Push a new TreeNode pointer P with the following properties:
             - its symbol is '$'
             - its children are A and B
             - its frequency is the sum of the frequencies of its children
        */

        TreeNode *P = new TreeNode('$', A->freq + B->freq);
        PQ.push(P);
    }

    /*
        Expected output:
            popped (D, 4) and (F, 5)
            popped (A, 6) and (B, 7)
            popped (E, 8) and ($, 9)
            popped ($, 13) and (C, 15)
            popped ($, 17) and ($, 28)
    */
}
