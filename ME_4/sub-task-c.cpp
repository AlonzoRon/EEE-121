#include<bits/stdc++.h>
using namespace std;

/*
    Sub-task C: You are given a weighted directed graph G
     - (4 pts) Complete the code below so that it prints all paths from vertex 1 to vertex 7
     - (2 pts) Bonus:   By adding one extra argument to backtrack() and print_path() functions,
                        modify the code so that print_path also prints the length of the path, i.e., the sum of weights of all its edges.
               Example: [1, 3, 8, 5, 7] length = 26
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

int vertex[1000];    // for backtracking

void print_path(int num_vertices){      // Note: num_vertices here is the number of vertices in the path to be printed.
    cout << "[";
    for(int i = 0; i < num_vertices; i++){
        if (i) cout << ", ";
        cout << vertex[i];
    }
    cout << "]";

    // Use this line only for the bonus item.
    // cout << "length = " << /* insert path length */ ;

    cout << endl;
}

void backtrack(Graph& G, int source, int dest, int idx){
    if (idx > 0 && vertex[idx - 1] == dest){
        print_path(idx);
        return;
    }

    if (idx == 0){
        vertex[idx] = source;
        backtrack(G, source, dest, idx + 1);
    }

    else{
        int curr = vertex[idx - 1];
        for(auto nxt : G.adj(curr)){
            vertex[idx] = nxt.first;
            backtrack(G, source, dest, idx + 1);
        }
    }
}

    /*
        Insert code here.

        Guide questions:
         - when idx == 0, which vertices are valid?
         source is valid
         - when idx != 0, which vertices are valid?
         any vertex in G.adj(vertex[idx - 1])
    */


void enumerate_path(Graph& G, int source, int dest){
    backtrack(G, source, dest, 0);
}

int main(){
    ifstream file("directed_graph.txt");

    int n, m;   // n - number of vertices, m - number of edges
    file >> n >> m;

    Graph G(n);

    for(int i = 0; i < m; i++){
        int u, v, weight;
        file >> u >> v >> weight;
        G.add_edge(u, v, weight);
    }

    enumerate_path(G, 1, 7);
}
