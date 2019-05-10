#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task B: You are given a weighted directed graph G
     - Implement the following code for finding shortest paths via recursive backtracking.
     - In this code, there are two arrays used for backtracking:
         - vertex[] for storing vertices
         - visited[] for keeping track of visited vertices  (Pay extra attention to this array!)
*/

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
};

int vertex[100];
bool visited[100];

int min_val = inf;

void backtrack(Graph& G, int source, int dest, int idx, int path_len){
    if (idx != 0 && vertex[idx - 1] == dest){
        if (path_len < min_val){
            min_val = path_len;
        }
        return;
    }

    if (idx == 0){
        vertex[idx] = source;
        visited[source] = true;

        backtrack(G, source, dest, idx + 1, 0);

        visited[source] = false;
    }
    else{
        int curr = vertex[idx - 1];

        /* Fix the following for-loop.*/

    int minimum = inf;
    for(auto nxt : G.adj(curr)){
        if(visited[nxt.first]) continue;
        if (nxt.second < minimum) minimum = nxt.second;
    }
    //cout << minimum << endl;

        for(auto nxt : G.adj(curr)){
            int nxt_id = nxt.first, nxt_cost = nxt.second;

            if (visited[nxt_id] || nxt_cost > minimum) continue;
            if (visited[dest]) break;
            cout << nxt_id << " " << nxt_cost << endl;


            vertex[idx] = nxt_id;
            visited[nxt_id] = true;

            backtrack(G, source, dest, idx + 1, path_len + nxt_cost);
        }
    }
}

void shortest_path(Graph& G, int source, int dest){
    int n = G.vertex_count();

    for(int i = 0; i < n; i++) visited[i] = false;

    backtrack(G, source, dest, 0, 0);

    cout << "shortest path length: " << min_val << endl;    // Expected output: 39
}

int main(){
    ifstream file("directed_graph.txt");
    int n, m;
    file >> n >> m;

    Graph G(n);

    for(int i = 0; i < m; i++){
        int u, v, weight;
        file >> u >> v >> weight;

        G.add_edge(u, v, weight);
    }

    int source = 0, dest = 8;

    shortest_path(G, source, dest);
}
