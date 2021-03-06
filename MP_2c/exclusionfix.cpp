#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

enum color{black, red, indifferent, no_color};

class Edge{
public:
    color edge_color;

    Edge(color given_color){
        edge_color = given_color;
    }
};

class Graph{
public:
    int num_vertices;
    vector<vector <int> > adjacency_list;
    vector<vector <Edge> > color_matrix;


    Graph(int vertices){
        num_vertices = vertices;
        adjacency_list.reserve(vertices);

        color_matrix.reserve(vertices);

        for(int i = 0; i < vertices; i++){
            color_matrix[i].reserve(vertices);
        }

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                color_matrix[i][j].edge_color = no_color;
            }
        }
    }

    void add_edge(int u, int v){
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }
};

void red_choose(vector<int> &red_sources, Graph &G, vector <vector <int> > &depth_list){
    vector<int> new_sources;
    for(auto source : red_sources){
        cout << source << endl;
        for(auto adjacent : G.adjacency_list[source]){
            Edge &curr_edge = G.color_matrix[source][adjacent];

            if(curr_edge.edge_color == black){
                continue;
            }

            else if(curr_edge.edge_color == no_color){
                new_sources.push_back(adjacent);
            }

            depth_list.push_back(new_sources);
            red_choose(new_sources, G, depth_list);
        }
    }
}

int main(){
    ifstream input("coffee_citydiamond.txt");
    int n, m;
    input >> n >> m;

    //Graph c_city(n);

    int total_vertices = n;
    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;
        total_vertices += (w*2) - 1;
    }

    int r, s;
    input >> r >> s;

    vector <int> black_shops;
    for(int i = 0; i < r; i++){
        int black_shop;
        input >> black_shop;

        black_shops.push_back(black_shop);
    }

    vector<int> red_shops;
    for(int i = 0; i < s; i++){
        int red_shop;
        input >> red_shop;

        red_shops.push_back(red_shop);
    }

    cout << total_vertices << endl;

    // after this part, we will now be creating the graph and re-reading the file
    //input.close();
    input.clear();
    input.seekg(0, ios::beg);

    Graph coffee_city(total_vertices); // creation of megagraph

    //ifstream input_vertices("coffee_citydiamond.txt");
    int x, y;
    input >> x >> y;

    //this code below assigns vertices to everything
    int curr_vertex = x - 1;
    for(int i = 0; i < y; i++){
        int u, v, w;
        input >> u >> v >> w;


        if(w == 1){
            curr_vertex++;
            coffee_city.add_edge(u, curr_vertex); // very first vertex
            cout << "paired" << u << "and"  << curr_vertex  << endl;
            cout << endl;


            coffee_city.add_edge(curr_vertex, v);
            cout << "paired" << curr_vertex << "and"  << v  << endl;
            cout << endl;
        }
        else{
            curr_vertex++;

            coffee_city.add_edge(u, curr_vertex);
            cout << "paired" << u << "and"  << curr_vertex  << endl;
            cout << endl;


        for (int i = 0; i < (w*2)-2; i++){
            coffee_city.add_edge(curr_vertex, curr_vertex + 1);
            cout << "paired" << curr_vertex << "and"  << curr_vertex + 1 << endl;
            curr_vertex++;
        }

        coffee_city.add_edge(curr_vertex, v);
        cout << "paired" << curr_vertex << "and"  << v << endl;
        cout << endl;

        }

    }
    //////////////

    vector<int> red_sources = {1};
    vector<vector <int> > depth_list;

    red_choose(red_sources, coffee_city, depth_list);



}
