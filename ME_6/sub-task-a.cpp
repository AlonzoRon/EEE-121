#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task A: You are given a weighted directed graph G
     - Implement the following (sub-optimal) greedy approach to finding shortest paths
         1. Start at the source vertex
         2. At each step, move to a vertex that (a) has not yet been visited, and (b) has the lowest cost
         3. Stop when the destination vertex is reached.
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

    int visited[n];
    for(int i = 0; i < n; i++) visited[i] = false;

    int curr = source;
    int path_len = 0;

    while(curr != dest){
        visited[curr] = true;

        int nxt_cost = inf;
        int nxt;

        for(auto test : G.adj(curr)){
            int test_id = test.first, test_cost = test.second;

            if (!visited[test.first] && test_cost < nxt_cost){
                nxt = test_id;
                nxt_cost = test_cost;
            }

        }

        if (nxt_cost == inf) break;

        curr = nxt;
        path_len += nxt_cost;
    }

    // Expected output: 278
    if (curr != dest)   cout << "There is no path from " << source << " to " << dest << endl;
    else                cout << "shortest path length: " << path_len << endl;
}
