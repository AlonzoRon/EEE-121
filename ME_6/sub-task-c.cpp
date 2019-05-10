#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task C: You are given a weighted directed graph G
     - Complete the following code for finding shortest paths using the Floyd-Warshall algorithm
     - Note: the Graph class internally uses an adjacency matrix representation
*/

const int inf = 1000000;

class Graph{
private:
    int num_vertices;
    vector<vector<int> > __adj; // adjacency *matrix*

public:
    Graph(int n) : num_vertices(n), __adj(n, vector<int>(n, inf)){
        for(int i = 0; i < n; i++) __adj[i][i] = 0;
    }

    int vertex_count(){
        return num_vertices;
    }

    void add_edge(int u, int v, int weight){
        __adj[u][v] = weight;
    }

    int edge_weight(int u, int v){
        return __adj[u][v];
    }
};

void shortest_path(Graph& G, int source, int dest){
    int n = G.vertex_count();

    int dist[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dist[i][j] = G.edge_weight(i, j);
        }
    }

    /*
        (2 pts) Fix the following nested for-loop
    */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    if (dist[source][dest] != inf)  cout << "shortest path length: " << dist[source][dest] << endl;
    else                            cout << "there is no path between " << source << " and " << dest << endl;
    /*
        (2 pts) Without declaring another array, print the shortest path from the source vertex to the destination vertex
                Hint: Start at the source vertex, and repeatedly use the dist[][] to determine the next vertex.
    */

    cout << source << endl;
    cout << dist[source][dest] << endl;

    /*
        Insert code here

        Possible output: 0 -> 5 -> 4 -> 8
    */
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
