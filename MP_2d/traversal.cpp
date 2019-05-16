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



vector <int> single_expansion(int src, Graph &G){
    vector<int> next_layer;
    for(auto adjacent : G.adjacency_list[src]){
        Edge &this_edge = G.color_matrix[src][adjacent];
        Edge &otherthis_edge = G.color_matrix[adjacent][src];

        if(this_edge.edge_color == no_color){
            this_edge.edge_color = red;
            otherthis_edge.edge_color = red;
            next_layer.push_back(adjacent);
        }
        else if(this_edge.edge_color == black || this_edge.edge_color == red){
            continue;
        }
    }

    for (auto newvertex : next_layer){
        cout << src << "---->" << newvertex << "     ";
    }
    cout << endl;

    return next_layer;

    //for (auto newvertex : next_layer){
    //    single_expansion(newvertex, G);
    //}
}

void whole_expansion(int src, Graph &G, vector <vector <pair <int, int> > > traversal_table,int layer = 0){
    vector<pair<int, int> > layer_vector;
    vector<int> sources = single_expansion(src, G);


    for (auto destination:sources){
        pair<int, int> pairing = {src, destination};
        layer_vector.push_back(pairing);
    }

    traversal_table.push_back(layer_vector);

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

    single_expansion(1, coffee_city);

}
