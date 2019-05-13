#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

enum EdgeColor{red, black, indifferent};

class Edge{
public:
    int subdivisions;
    int num_red = 0;
    int num_black = 0;

    Edge(int subdivisions);

};

Edge::Edge(int subdivisions){
    this -> subdivisions = subdivisions;
}

class Graph{
public:
    int num_vertices;
    vector<vector <int> > adjacency_list;
    vector <vector <Edge> > adjacency_edgematrix;

    Graph(int num_vertices);

    void add_edge(int u, int v, Edge e);

};

Graph::Graph(int num_vertices){
    this -> num_vertices = num_vertices;
    this -> adjacency_list.reserve(num_vertices);

    this -> adjacency_edgematrix.reserve(num_vertices);
    for(int i = 0; i < num_vertices; i++){
        this -> adjacency_edgematrix[i].reserve(num_vertices);
    }
}

void Graph::add_edge(int u, int v, Edge e){
    this -> adjacency_edgematrix[u][v] = e;
    this -> adjacency_edgematrix[v][u] = e;

    this -> adjacency_list[u].push_back(v);
    this -> adjacency_list[v].push_back(u);
}

bool visited[1000][1000];
void spanner_red(int vertex, Graph &G, int prev_vertex){
    for(auto adjacent:G.adjacency_list[vertex]){
        //if already previously visited, continue;
        if(visited[vertex][adjacent] || visited[adjacent][vertex]) continue;

        Edge &edge_curr = G.adjacency_edgematrix[vertex][adjacent];
        Edge &otheredge_curr = G.adjacency_edgematrix[adjacent][vertex];

        if(edge_curr.subdivisions != 0){
            edge_curr.num_red += 1;
            otheredge_curr.num_red += 1;

            edge_curr.subdivisions -= 1;
            otheredge_curr.subdivisions -= 1;
        }

        else if(edge_curr.subdivisions == 0 && edge_curr.num_black > 0){
            continue;
        }

        else if(edge_curr.subdivisions == 0 && edge_curr.num_black == 0){
            cout << "marked" << vertex << " and  " << adjacent << endl;
            visited[vertex][adjacent] = true;
            visited[adjacent][vertex] = true;
            spanner_red(adjacent, G, prev_vertex);

        }
    }

}

int coverage_counter_red(Graph &G, int n){
    int num_red = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            num_red += G.adjacency_edgematrix[i][j].num_red;
        }
    }

    return num_red;
}
int coverage_counter(Graph &G, int n){
    int no_subdi = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            no_subdi += G.adjacency_edgematrix[i][j].subdivisions;
        }
    }

    return no_subdi;
}


int main(){
    ifstream input("coffee_city_3x2.txt");

    int n, m;
    input >> n >> m;

    Graph city = Graph(n);

    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;

        Edge e = Edge(w * 2);
        //cout << "went in" << endl;
        city.add_edge(u, v, e);
    }

    for(int i = 0; i < n; i++){
        for (auto x : city.adjacency_list[i]){
            cout << x << " ";
        }
        cout << endl;
    }

    int initial_coverage = coverage_counter(city, n);
    cout << coverage_counter(city, n) << endl;

    while(coverage_counter(city, n) != 0){
        spanner_red(0, city, -100000);
    }



    cout << endl;
    int redcov = coverage_counter_red(city, n);
    double percent = (double)redcov/(double)initial_coverage * 100;
    cout << percent << "%" << endl;

}
