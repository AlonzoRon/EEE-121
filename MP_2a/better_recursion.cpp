#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

enum EdgeColor{red, black, indifferent};
bool visited[1000][1000];

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

vector <int> full_red;
void expand_red(Graph &G, int src){

    for (auto adjacent : G.adjacency_list[src]){

        bool tocontinue = false;
        for (auto vertex : full_red){
            if (vertex == adjacent) tocontinue = true;
        }
        if (tocontinue) continue;

        Edge &edge1 = G.adjacency_edgematrix[src][adjacent];
        Edge &edge2 = G.adjacency_edgematrix[adjacent][src];

        if(edge1.subdivisions > 0){
            edge1.num_red += 1;
            edge2.num_red += 1;
            edge1.subdivisions -= 1;
            edge2.subdivisions -= 1;
            cout << "new numbers (red), subdivisions: " << edge1.num_red << " " << edge2.subdivisions << endl;
        }

        else if(edge1.subdivisions == 0 && edge1.num_black > 1){
            continue;
        }

        else if(edge1.subdivisions == 0 && edge1.num_black == 0){
            full_red.push_back(src);
            expand_red(G, adjacent);
        }
    }
}


int main(){
    ifstream input("coffee_city_example.txt");

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

    for(int i = 0; i < 1000; i++){
        expand_red(city, 0);
    }

    int initial_coverage = coverage_counter(city, n);
    cout << coverage_counter(city, n) << endl;


    cout << endl;
    int redcov = coverage_counter_red(city, n);
    double percent = (double)redcov/(double)initial_coverage * 100;
    //initial_coverage * 100;
    cout << percent << "%" << endl;

}
