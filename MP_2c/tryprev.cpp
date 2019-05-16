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


void redpair_chooser(int src, Graph &G, vector <pair <int, int> > &pairs, vector <int> &exclusion, int prev_vertex){

    for (auto adjacent:G.adjacency_list[src]){
        Edge &curr_edge = G.color_matrix[src][adjacent];
        //cout << "current source: " << src << endl;

        if(adjacent == prev_vertex) continue;

        //bool moveon = false;
        //for (auto exclude : exclusion){
        //    if (adjacent == exclude){
        //        moveon = true;
        //        break;
        //    }
        //}

        //if(moveon) continue;

        else if(curr_edge.edge_color == red){
            exclusion.push_back(src);
            redpair_chooser(adjacent, G, pairs, exclusion, src);
        }
        else if(curr_edge.edge_color == no_color){
            pairs.push_back({src, adjacent});
            cout << "added to colorlist" << endl;
            continue;
        }
        else if(curr_edge.edge_color == black){
            continue;
        }
    }
}

void red_painter(vector <pair <int, int> > &reds, Graph &G){

    for (auto pair: reds){
        int src, dest;
        src = pair.first;
        dest = pair.second;

        Edge &curr_edge = G.color_matrix[src][dest];
        Edge &othercurr_edge = G.color_matrix[dest][src];

        curr_edge.edge_color = red;
        othercurr_edge.edge_color = red;
    }

    reds.clear();


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

    vector <pair <int, int> > redtobe_edges;
    vector <int> red_exclusion;

    for(int i = 0; i < 10; i++){
        redpair_chooser(1, coffee_city, redtobe_edges, red_exclusion, -10000);
        for (auto pair: redtobe_edges){
            cout << pair.first << "---->" << pair.second << "    ";
        }
        cout << endl;
        red_painter(redtobe_edges, coffee_city);
    }


}
