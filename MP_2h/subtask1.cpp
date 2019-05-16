#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<cmath>
using namespace std;


int inf = 10000000;
enum color{black, red, indifferent, no_canvas, blank_canvas};

class Edge{
public:
    color edge_color;

    Edge(color edgecolor){
        edge_color = edgecolor;
    }

};

class Graph{
public:
    int num_vertices;
    list<pair<int, int> > *adj;
    vector<vector <Edge> > color_matrix;
    vector<pair <color, int> > vertex_colors;
    vector<vector <int> > weight_matrix;


    Graph(int vertices){ // constructor
        num_vertices = vertices;
        adj = new list <pair<int, int> > [vertices];

        color_matrix.reserve(vertices);
        for(int i = 0; i < vertices; i++){
            color_matrix[i].reserve(vertices);
        }

        weight_matrix.reserve(vertices);
        for(int i = 0; i < vertices; i++){
            weight_matrix[i].reserve(vertices);
        }

    }

    void add_edge(int u, int v, int w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});

        weight_matrix[u][v] = w;
        weight_matrix[v][u] = w;

        color_matrix[u][v] = blank_canvas;
        color_matrix[v][u] = blank_canvas;

        // sets the colors as blank canvases, meaning the edge exists but
        // currently not yet colored
    }

    vector <int> dijkstra(int src){ // implementation of dijkstra's algorithm to get the shortest path
        priority_queue<pair <int, int>, vector <pair <int, int> >, greater<pair <int, int> > > pq;

        vector<int> dist(num_vertices, inf);

        pq.push({0,     src});
        dist[src] = 0;

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for(auto adjacent:adj[u]){
                int v = adjacent.first;
                int weight = adjacent.second;

                if (dist[v] > dist[u] + weight){
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // for(int i = 0; i < num_vertices; i++){
        //     cout << i << " ----> " << dist[i] << endl;
        // }
        return dist;
    }

    void vertex_colors_printer(){
        int i = 0;
        for(auto vertex:vertex_colors){
            cout << i << " ";
            color curr_color;
            int vertex_value;

            curr_color = vertex.first;
            vertex_value = vertex.second;

            if(curr_color == red) cout << "red ";
            else if(curr_color == black) cout << "black ";
            else if(curr_color == indifferent) cout << "indifferent ";

            cout << vertex_value << endl;
            i++;
        }
    }


};

vector<int> finalizer(vector<int> shop_locations, Graph &G){
    vector<int> summary;

    vector<vector<int> > unsorted_list;
    for (auto shop:shop_locations){
        unsorted_list.push_back(G.dijkstra(shop));
    }

    for (int i = 0; i < G.num_vertices; i++){
        int lowest = 100000;
        for (auto indiv_shopsummary:unsorted_list){
            if(indiv_shopsummary[i] < lowest){
                lowest = indiv_shopsummary[i];
            }
        }
        summary.push_back(lowest);
    }
    return summary;
}

void vertex_painter(vector<int> black_list, vector<int> red_list, Graph &G){
    for(int i = 0; i < G.num_vertices; i++){
        //cout << i << "  ";
        //cout << "red: " << red_list[i] << " vs. black:  " << black_list[i];
        if(red_list[i] < black_list[i]){
            G.vertex_colors.push_back({red, red_list[i]});
            //cout << " pushed red" << endl;
        }
        else if(black_list[i] < red_list[i]){
            G.vertex_colors.push_back({black, black_list[i]});
            //cout << " pushed black" << endl;
        }
        else if(black_list[i] == red_list[i]){
            G.vertex_colors.push_back({indifferent, red_list[i]});
            //cout << " pushed indifferent" << endl;
        }
    }
}

int distance_calculator(int non_red, int red, Graph &G){
    int non_red_dist, red_dist, edge_weight;
    int distance;

    non_red_dist = G.vertex_colors[non_red].second;
    red_dist = G.vertex_colors[red].second;
    edge_weight = G.weight_matrix[red][non_red];

    distance =  (((red_dist + non_red_dist + edge_weight) / 2) - non_red_dist);

    return distance;
}

int coverage_calculator(Graph &G){
    vector<vector<bool > > visited;
    visited.reserve(G.num_vertices);
    for(int i = 0; i < G.num_vertices;i++){
        visited[i].reserve(G.num_vertices);
    }

    int total_red = 0;

    for(int i = 0; i < G.num_vertices; i++){
        for (auto destination:G.adj[i]){
            //their vertex_colors
            //their vertex_distances
            //edge-to-edge weight


            int dest = destination.first;
            cout << "current s/d: " << i << "->>" << dest << endl;
            int edge_weight = destination.second;

            color source_color = G.vertex_colors[i].first;
            int source_dist = G.vertex_colors[i].second;

            color dest_color = G.vertex_colors[dest].first;
            int dest_dist = G.vertex_colors[dest].second;

            if(visited[i][dest]) {
                cout << "this has been visited" << endl;
                continue;
            }

            if(source_color == red){
                if (dest_color == red){
                    total_red += edge_weight;
                    cout << "source" << i << "   dest" << dest << "  added -->" << edge_weight << endl;
                }
                else if (dest_color == black){
                    total_red += distance_calculator(i, dest, G);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(i, dest, G) << endl;
                }
                else if (dest_color == indifferent){
                    total_red += distance_calculator(i, dest, G);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(i, dest, G) << endl;;
                }

            }

            else if(source_color == black){
                if (dest_color == red){
                    total_red += distance_calculator(dest, i, G);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(dest, i, G) << endl;
                }
            }

            else if(source_color == indifferent){
                if (dest_color == red){
                    total_red += distance_calculator(dest, i, G);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(dest, i, G) << endl;
                }
            }

            visited[i][dest] = true;
            visited[dest][i] = true;
            cout << "marked "  << i << "-->" << dest << "  as visited" << endl;
        }
    }

    return total_red;
}

void coverage_printer(int num_red, int edges){
    double coverage;

    coverage = (double) num_red / (double) edges;

    coverage *= 10000;
    coverage = round(coverage);
    coverage /= 100;

    cout << coverage << "% coverage." << endl;
}

int main(){
    ifstream input("coffee_city.txt");
    int n, m;
    input >> n >> m;

    int total_vertices = n;

    Graph coffee_city(total_vertices); // created the coffee city Graph
    int totaledge_weight = 0;

    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;

        coffee_city.add_edge(u, v, w * 2);
        totaledge_weight += w * 2;
        // we use w * 2 to prevent any problems with 0.5 for integers
    }

    int r, s;
    int number_red, number_black;
    input >> r >> s;

    number_black = r;
    number_red = s;

    vector<int> black_shops;
    for(int i = 0; i < number_black; i++){
        int black_shop;
        input >> black_shop;

        black_shops.push_back(black_shop);
    }

    vector<int> red_shops;
    for(int i = 0; i < number_red; i++){
        int red_shop;
        input >> red_shop;

        red_shops.push_back(red_shop);
    }

    vector<int> black_summary; black_summary.reserve(total_vertices);
    vector<int> red_summary; red_summary.reserve(total_vertices);

    black_summary = finalizer(black_shops, coffee_city);
    red_summary = finalizer(red_shops, coffee_city);

    vertex_painter(black_summary, red_summary, coffee_city);
    //coffee_city.vertex_colors_printer();

    int red_count = coverage_calculator(coffee_city);

    coverage_printer(red_count, totaledge_weight);



    //distance_calculator(1, 2, coffee_city);

    //coverage_calculator(coffee_city) // returns the weight of all red

    //for(auto x:coffee_city.adj[0]){
    //    cout << x.first << endl;
    //}



    //int i = 0;
    //for(auto x:black_summary){
    //    cout << i << " ---> ";
    //    cout << x << endl;
    //    i++;
    //}



    //coffee_city.dijkstra(5);
}
