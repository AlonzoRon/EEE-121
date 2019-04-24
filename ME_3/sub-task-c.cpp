#include<bits/stdc++.h>
using namespace std;

const int inf = 1000000;

class Graph{
private:
    int num_vertices;
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

    vector<int> shortest_path(int source, int dest);
};

vector<int> Graph::shortest_path(int source, int dest){
    int key[num_vertices];
    int pred[num_vertices];

    bool in_tree[num_vertices];

    for(int i = 0; i < num_vertices; i++){
        key[i] = inf;
        pred[i] = -1;   // -1 -> no predecessor (yet)
        in_tree[i] = false;
    }

    key[source] = 0;
    pred[source] = source;

    for(int loop_ctr = 0; loop_ctr < num_vertices; loop_ctr++){
        int curr_id;


        int large_num = 1000000;
        for(auto x:this->adj(source)){
            if (x.second < large_num){
                curr_id = x.first;
                large_num = x.second;
            }
        }
        /*
            1 point: Identify the vertex with the lowest key
                     that is not yet in the shortest-path tree, and save it to curr_id.
        */

        in_tree[curr_id] = true;

        for(auto nxt : __adj[curr_id]){
            int nxt_id = nxt.first, nxt_cost = nxt.second;

            key[nxt_id] = nxt_cost;
            pred[nxt_id] = curr_id;
            /*
                1 point: Update key[nxt_id] and pred[nxt_id], if possible.
            */
        }
    }

    vector<int> path;


    int i = 0;
    for (auto x:pred){
        //cout << x << endl;
        if (x != -1) path.push_back(i);
        i++;
    }
    /*
        1 point: Use the pred[] array
                 to list all vertices in a shortest path from source to dest.
                 Store the result in "path"

        Notes:
         - The first element should be source and the last element should be dest.
         - If there is no shortest path, "path" should be empty.
    */

    return path;

    /*
        1 point: What is the running time complexity of this function?
                 Use V for the number of vertices, and E for the number of edges.

        Type your answer here: O(VE)
    */
}

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
    ifstream file("directed_graph.txt");
    int n, m;           // n - number of vertices, m - number of edges
    file >> n >> m;

    Graph G(n);

    // read graph from file
    for(int i = 0; i < m; i++){
        int u, v, weight;
        file >> u >> v >> weight;

        G.add_edge(u, v, weight);
    }

    cout << G.shortest_path(0, 7) << endl; // Expected output: [0, 4, 1, 3, 7]
    cout << G.shortest_path(1, 3) << endl; // Expected output: [1, 3]
    cout << G.shortest_path(3, 4) << endl; // Expected output: []
}
