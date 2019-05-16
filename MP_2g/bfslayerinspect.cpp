#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

enum color{black, red, indifferent, no_canvas, blank_canvas};

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
    vector<color> vertex_color;


    Graph(int vertices){
        num_vertices = vertices;
        adjacency_list.reserve(vertices);

        color_matrix.reserve(vertices);
        vertex_color.reserve(vertices);

        for(int i = 0; i < vertices; i++){
            color_matrix[i].reserve(vertices);
        }

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                color_matrix[i][j].edge_color = no_canvas;
            }
        }
    }


    void add_edge(int u, int v){
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);

        color_matrix[u][v] = blank_canvas;
        color_matrix[v][u] = blank_canvas;
    }
};

vector <int> BFS_lengthcalc(Graph &G, int src){
    vector <int> return_vector;
    int level[G.num_vertices];
    bool marked[G.num_vertices];

    queue<int> que;
    que.push(src);
    level[src] = 0;
    marked[src] = true;

    while(!que.empty()){
        src = que.front();
        que.pop();

        for (int i = 0; i < G.adjacency_list[src].size(); i++){
            int b = G.adjacency_list[src][i];

            if(!marked[b]){
                que.push(b);
                level[b] = level[src] + 1;

                marked[b] = true;
            }
        }
    }

    for(int i = 0; i < G.num_vertices; i++){
        return_vector.push_back(level[i]);

    }
    return return_vector;
}

void set_color(vector<int> red_distances, vector<int> black_distances, Graph &G){
    for(int i = 0; i < G.num_vertices; i++){
        if(red_distances[i] < black_distances[i]){
            G.vertex_color[i] = red;
        }
        else if(black_distances[i] < red_distances[i]){
            G.vertex_color[i] = black;
        }
        else if(black_distances[i] == red_distances[i]){
            G.vertex_color[i] = indifferent;
        }
    }
}

void colorize(Graph &G){
    vector<color> &vertexcolor = G.vertex_color;
    for(int i = 0; i < G.num_vertices; i++){

        for(int j = 0; j < G.num_vertices; j++){
            color &matrix_color = G.color_matrix[i][j].edge_color;
            color &othermatrix_color = G.color_matrix[i][j].edge_color;

            if(matrix_color == blank_canvas){

                if(vertexcolor[i] == red && vertexcolor[j] == red){
                    matrix_color = red;
                    othermatrix_color = red;
                }
                else if(vertexcolor[i] == black && vertexcolor[j] == black){
                    matrix_color = black;
                    othermatrix_color = black;
                }
                else if(vertexcolor[i] == indifferent && vertexcolor[j] == indifferent){
                    matrix_color = indifferent;
                    othermatrix_color = indifferent;
                }
                else if((vertexcolor[i] == indifferent && vertexcolor[j] == red) ||
                        (vertexcolor[i] == red && vertexcolor[j] == indifferent)){
                    matrix_color = red;
                    othermatrix_color = red;
                }
                else if((vertexcolor[i] == indifferent && vertexcolor[j] == black) ||
                        (vertexcolor[i] == black && vertexcolor[j] == indifferent)){
                    matrix_color = black;
                    othermatrix_color = black;
                }
            }
        }
    }
}

int color_counter(Graph &G){
    double c_red = 0;
    double c_black = 0;
    double c_indifferent = 0;
    double c_total = 0;
    for(int i = 0; i < G.num_vertices; i++){
        for(int j = 0; j < G.num_vertices; j++){
            color &curr_edgecolor = G.color_matrix[i][j].edge_color;

            if(curr_edgecolor != no_canvas) c_total++;
            if(curr_edgecolor == red) c_red++;
            if(curr_edgecolor == black) c_black++;
            if(curr_edgecolor == indifferent) c_indifferent++;

        }
    }

    cout << "red: " << c_red << endl;
    cout << "black: " << c_black << endl;
    cout << "indifferent: " << c_indifferent << endl;
    cout << "total: " << c_total << endl;

    double percentage = c_red/c_total;
    cout << percentage << endl;
    percentage = percentage * 10000;
    return percentage;

}

int main(){
    ifstream input("coffee_city.txt");
    int n, m;
    input >> n >> m;

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

    // after this part, we will now be creating the graph and re-reading the file

    input.clear();
    input.seekg(0, ios::beg);

    Graph coffee_city(total_vertices); // creation of mega-graph

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


            coffee_city.add_edge(curr_vertex, v);
        }
        else{
            curr_vertex++;

            coffee_city.add_edge(u, curr_vertex);


        for (int i = 0; i < (w*2)-2; i++){
            coffee_city.add_edge(curr_vertex, curr_vertex + 1);
            curr_vertex++;
        }

        coffee_city.add_edge(curr_vertex, v);

        }
    }

    // two arrays that tell the shortest distance between a certain vertex
    // and a colored shop (these will be compared later to color the roads)
    vector<int> red_distances;
    vector<int> black_distances;

    //evaluate red_distances first;

    vector<vector <int> > allred_shops;
    for(auto red:red_shops){
        allred_shops.push_back(BFS_lengthcalc(coffee_city, red));
    }

    for(int i = 0; i < coffee_city.num_vertices; i++){
        int minimum = 100000000;
        for(auto j: allred_shops){
            if (j[i] < minimum) minimum = j[i];
        }
        red_distances.push_back(minimum);
    }


    //then evaluate the black distances

    vector<vector <int> > allblack_shops;
    for(auto black:black_shops){
        allblack_shops.push_back(BFS_lengthcalc(coffee_city, black));
    }

    for(int i = 0; i < coffee_city.num_vertices; i++){
        int minimum = 100000000;

        for(auto j: allblack_shops){
            if (j[i] < minimum) minimum = j[i];
        }
        black_distances.push_back(minimum);
    }


    set_color(red_distances, black_distances, coffee_city);

    // time to fill in the color_matrix

    colorize(coffee_city);
    double number = color_counter(coffee_city);
    number /= 100;
    cout << number << "%" << endl;

}
