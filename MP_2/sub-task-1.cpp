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
    vector<vector<pair<int, Edge> > > adjacency_list;

    Graph(int num_vertices); //initialize

    void add_edge(int u, int v, Edge E);

};

Graph::Graph(int num_vertices){
    this -> num_vertices = num_vertices;
    this -> adjacency_list.reserve(num_vertices);
}

void Graph::add_edge(int u, int v, Edge e){
    cout << "added edge" << endl;

    pair<int, Edge> p1 = {v, e};
    pair<int, Edge> p2 = {u, e};

    this -> adjacency_list[u].push_back(p1);
    this -> adjacency_list[v].push_back(p2);
    // make sure that edge e points to the same edge
    // or just edit both edges which should work lol

}

void spanner(int vertex, EdgeColor color, Graph &G){
    if (color == red){
        for (auto adjacent : G.adjacency_list[vertex]){
            int curr_vertexto;
            curr_vertexto = adjacent.first;

            Edge curr_edge_dupe(0);
            for(auto adj : G.adjacency_list[curr_vertexto]){
                if (adj.first == vertex){
                    curr_edge_dupe = adj.second;
                    break;
                }
            }
            //locate index of edge from adjacency list of vertexto

            Edge curr_edge(0);
            curr_edge = adjacent.second;

            if (curr_edge.subdivisions != 1){
                curr_edge_dupe.num_red += 1;
                curr_edge.subdivisions -= 1;
                curr_edge.num_red += 1;
                curr_edge.subdivisions -= 1;

            }


        }

    }
    else if (color == black){

    }
}

int main(){
    ifstream input("coffee_city_example.txt");

    int n, m;
    input >> n >> m;

    Graph city = Graph(n);

    cout << m << endl;


    for(int i = 0; i < m; i++){
        int u, v, w;
        // first junction is always vertex 0
        // second junction is named vertex 1
        input >> u >> v >> w;
        //cout << u << v << w << endl;

        Edge e = Edge(w * 2);
        city.add_edge(u, v, e);

        //num_vertices += w * 2;
    }

    EdgeColor color = red;

    spanner(0, color, city);

    cout << "number of red: ";
    cout << city.adjacency_list[0][3].second.num_red << endl;




}
