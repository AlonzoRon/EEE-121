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

void spanner(int vertex, EdgeColor color, Graph &G, int prev_vertex){
    for(auto adjacent:G.adjacency_list[vertex]){

        //if(adjacent == prev_vertex) continue;
        if(visited[vertex][adjacent] || visited[adjacent][vertex]) continue;


        Edge &curr_edge = G.adjacency_edgematrix[vertex][adjacent];
        Edge &other_edge = G.adjacency_edgematrix[adjacent][vertex];

        //if (visited[vertex][adjacent] && curr_edge.subdivisions == 0) continue;
        //visited[vertex][adjacent] = true;

        //cout << "Current pairing: " << vertex << "-->" << adjacent << endl;

        if(color == red){
            if(curr_edge.subdivisions != 0){
                curr_edge.num_red += 1;
                other_edge.num_red += 1;

                curr_edge.subdivisions -= 1;
                other_edge.subdivisions -= 1;
            }
            else if(curr_edge.subdivisions == 0 && curr_edge.num_black == 0){
                //cout << "pumasok rito" << endl;
                cout << "tagged " << vertex << " and " << adjacent  << endl;
                visited[vertex][adjacent] = true;
                visited[adjacent][vertex] = true;
                spanner(adjacent, color, G, vertex);
                //implement recursive shit
            }
            else if(curr_edge.subdivisions == 0 && curr_edge.num_black > 0){
                continue;
            }
            cout << "new numbers (red), subdivisions: " << curr_edge.num_red << " " << curr_edge.subdivisions << endl;
            //cout << "black " << curr_edge.num_black << endl;


        }

        else if (color == black){
            if(curr_edge.subdivisions != 0){
                curr_edge.num_black += 1;
                other_edge.num_black += 1;

                curr_edge.subdivisions -= 1;
                other_edge.subdivisions -= 1;
            }
            else if(curr_edge.subdivisions == 0 && curr_edge.num_red == 0){
                //cout << "pumasok rito" << endl;
                spanner(adjacent, color, G, vertex);
                //implement recursive shit
            }
            else if(curr_edge.subdivisions == 0 && curr_edge.num_red > 0){
                continue;
            }
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
        //spanner(0, red, city, -100000);
        //spanner(2, black, city, -100000);
        //cout << "iterate" << endl;
        //spanner(0, black, city, -100000);

        spanner(1, red, city, -100000);

        //spanner(2, red, city, -10000);
        //spanner(5, black, city, -10000);
        //spanner(9, black, city, -10000);
        //cout << "coverage: " << coverage_counter(city, n) << endl;
    }


    //for (auto x : city.adjacency_list[0]){
    //    cout << x << " ";
    //}
    cout << endl;
    int redcov = coverage_counter_red(city, n);
    double percent = (double)redcov/(double)initial_coverage * 100;
    //initial_coverage * 100;
    cout << percent << "%" << endl;

    //cout << city.adjacency_edgematrix[0][1].subdivisions << endl;
    //cout << city.adjacency_edgematrix[0][1].num_red << endl;
//
    //cout << endl;
//
    //cout << city.adjacency_edgematrix[1][2].subdivisions << endl;
    //cout << city.adjacency_edgematrix[1][2].num_red << endl;

}
