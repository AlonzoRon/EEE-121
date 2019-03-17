class BSTNode{
friend class BSTree;

private:
    int data;
    BSTNode *left, *right;
    
    BSTNode(int data) : data(data), left(nullptr), right(nullptr){}
    ~BSTNode();
    
    void insert(int);
    bool find(int);
    void print();
};

class BSTree{
private:
    BSTNode *root;

public:
    BSTree() : root(nullptr){}
    ~BSTree();
    
    void insert(int);
    bool find(int);
    void print();
};

BSTNode::~BSTNode(){
    delete left;
    delete right;
}

// Part (a): Complete the following function
void BSTNode::insert(int val){
    if (data == val) return;
    
    if (val < data){
        if (left == nullptr)    left = new BSTNode(val);
        else                    left -> insert(val);
    }
    else{
        if (right == nullptr)   right = new BSTNode(val);
        else                    right -> insert(val);
    }
    
    return;
}

// Part (c): Implement the following function recursively
//           so that BSTree::print() outputs the contents in sorted order.
// 
// Note:     Use std::cout for printing to avoid compile-time errors.
void BSTNode::print(){
    
    if(left == nullptr) {
    std::cout << data;
    
    }
    else left -> print();

}

// Part (d): Convert the following into an iterative function.
bool BSTNode::find(int val){
    if (data == val) return true;
    
    if (val < data){
        if (left == nullptr)    return false;
        else                    left-> find(val);
    }
    else{
        if (right == nullptr)   return false;
        else                    right-> find(val);
    }
}

BSTree::~BSTree(){
    delete root;
}

void BSTree::insert(int val){
    if (root) root-> insert(val);
    else root = new BSTNode(val);
}

bool BSTree::find(int val){
    return root-> find(val);
}

void BSTree::print(){
    root-> print();
}
