#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

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
    vector<vector<int> > adjacency_list;

    Graph(int num_vertices); //initialize

    void add_edge(int u, int v);


};

Graph::Graph(int num_vertices){
    this -> num_vertices = num_vertices;
}

void Graph::add_edge(int u, int v){
    cout << "added edge" << endl;

    //pair<int, Edge> p1 = {v, e};
    //pair<int, Edge> p2 = {u, e};

    //this -> adjacency_list[u].push_back(p1);
    //this -> adjacency_list[v].push_back(p2);

    this -> adjacency_list[u].push_back(v);
    this -> adjacency_list[v].push_back(u);
    // make sure that edge e points to the same edge
    // or just edit both edges which should work lol

}

int main(){
    ifstream input("coffee_city_example.txt");

    int n, m;
    input >> n >> m;

    Graph city = Graph(n);

    vector <vector <int> > v;

    vector<int> vin = {1, 2, 3};
    v.push_back(vin);

    v[1].push_back(1);

    for (auto x: v[0]){
        cout << x << endl;
    }





}
