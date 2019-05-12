#include<bits/stdc++.h>
using namespace std;

const int inf = 1000000;

class Graph{
private:
    int num_vertices; //vertices are named 0 - n-1
    vector<vector<pair<int, int> > > __adj;

public:
    Graph(int n) : num_vertices(n), __adj(n){}

    int vertex_count(){
        return num_vertices;
    }

    void add_edge(int u, int v, int weight){
        __adj[u].push_back({v, weight});
    }

    vector<pair<int, int> >& adj(int v){
        return __adj[v];
    }

    //vector<int> shortest_path(int source, int dest);
};


template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v){
    os << "[";

    bool flag = false;
    for(auto x : v){
        if (flag) os << ", ";

        flag = true;
        os << x;
    }
    os << "]";
    return os;
}

int main(){
    ifstream file("labeled_graph.txt");

    int n, m;           // n - number of vertices, m - number of edges
    file >> n >> m;

    Graph G(n);
    string label[n];

    // Read vertex labels;

    for(int i = 0; i < n; i++){
        file >> label[i];
    }

    unordered_map<string, int> H;

    for(int i = 0; i < n; i++){
        H[label[i]] = i;
    }
    /*
        Sub-task A: Use an unordered_map H that maps each label to an integer as follows:
         - the first string in the list is assigned to 0
         - the second string is assigned to 1
         - the third string is assigned to 2
         - ... and so on
    */

    for(int i = 0; i < m; i++){
        string label_u, label_v;
        int weight;

        file >> label_u >> label_v >> weight;

        G.add_edge(H[label_u], H[label_v], weight);
    }

    /*
        Sub-task B: Complete the code below that prints all vertices reachable from LOU.
        Possible output: ZSZ IYY TKE ERQ LOU.
    */

    bool visited[n] = {0};
    int source = H["LOU"]; // Fill in the blank

    queue<int> Q;

    Q.push(source);

    while(!Q.empty()){
        int curr_id = Q.front();
        Q.pop();

        visited[curr_id] = true;

        for(auto nxt : G.adj(curr_id)){
            int nxt_id = nxt.first;
            if (!visited[nxt_id]) Q.push(nxt_id);
        }
    }

    for(int i = 0; i < n; i++){
        if (visited[i]){
            cout << label[i] << endl;
        }


    }

    /*
        Insert code to print labels of visited vertices.
    */
}
