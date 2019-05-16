#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<cmath>
#include<algorithm>
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

    Graph(int vertices){ // constructor
        num_vertices = vertices;
        adj = new list <pair<int, int> > [vertices];

        color_matrix.reserve(vertices);
        for(int i = 0; i < vertices; i++){
            color_matrix[i].reserve(vertices);
        }

        vertex_colors.reserve(vertices);
    }

    void add_edge(int u, int v, int w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});

        color_matrix[u][v] = blank_canvas;
        color_matrix[v][u] = blank_canvas;

        // sets the colors as blank canvases, meaning the edge exists but
        // currently not yet colored
    }

    vector <int> dijkstra(int src){ // implementation of dijkstra's algorithm to get the shortest path
        priority_queue<pair <int, int>, vector <pair <int, int> >, greater<pair <int, int> > > pq;

        vector<int> dist(num_vertices, inf);

        pq.push({0, src});
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

        return dist;
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

        if(red_list[i] < black_list[i]){
            G.vertex_colors[i] = {red, red_list[i]};
        }
        else if(black_list[i] < red_list[i]){
            G.vertex_colors[i] = {black, black_list[i]};
        }
        else if(black_list[i] == red_list[i]){
            G.vertex_colors[i] = {indifferent, red_list[i]};
        }
    }
}

void vertex_unpainter(Graph &G){
    G.vertex_colors.clear();
}

int distance_calculator(int non_red, int red, Graph &G,int edge_weight){
    int non_red_dist, red_dist;
    int distance;

    non_red_dist = G.vertex_colors[non_red].second;
    red_dist = G.vertex_colors[red].second;

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
            int edge_weight = destination.second;
            color source_color = G.vertex_colors[i].first;
            color dest_color = G.vertex_colors[dest].first;

            if(visited[i][dest]) {
                continue;
            }

            if(source_color == red){
                if (dest_color == red){
                    total_red += edge_weight;
                }
                else if (dest_color == black){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                }
                else if (dest_color == indifferent){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                }

            }

            else if(source_color == black){
                if (dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                }
            }

            else if(source_color == indifferent){
                if (dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                }
            }

            visited[i][dest] = true;
            visited[dest][i] = true;
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

vector<vector<int> > combinations_generator(int possible_positions, int red_shopnumber){
    vector<vector<int> > megalist;

    vector<bool> v(possible_positions);
    fill(v.begin(), v.begin() + red_shopnumber, true);

    do{
        vector<int> current;
        for(int i =0; i < possible_positions; i++){
            if (v[i]){
                cout << i << " ";
                current.push_back(i);
            }
        }
        megalist.push_back(current);
        cout << endl;
    } while(prev_permutation(v.begin(), v.end()));

    return megalist;
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
    int number_redwanted, number_black;
    input >> r >> s;

    number_black = r;

    vector<int> black_shops;
    for(int i = 0; i < number_black; i++){
        int black_shop;
        input >> black_shop;

        black_shops.push_back(black_shop);
    }

    vector<int> black_summary; black_summary.reserve(total_vertices);
    black_summary = finalizer(black_shops, coffee_city);
    //at this point black is final, but red won't be

    // this is the part when we count the number of available shop_locations
    // and generate ALL possible combinations of n(available slots) container
    //then iterate and compare the values and get the highest one

    number_redwanted = s;
    int possible_positions = coffee_city.num_vertices - number_black;

    cout << possible_positions << endl;

    vector< vector< int> > combis = combinations_generator(possible_positions, number_redwanted);

    //make a vector sized 0 - 13

    vector<int> positions_vertex;
    //fill this vector of only possible

    for(int i = 0; i < coffee_city.num_vertices; i++){
        bool inside_black = false;
        for(auto black: black_shops){
            if(i == black){
                inside_black = true;
                break;
            }
        }
        if (inside_black) continue;
        positions_vertex.push_back(i);
    }


    for(auto x: positions_vertex){
        cout << x << " ";
    }
    cout << endl;

    // at this point positions[index] pertains to the TRUE position and not the index

    for(auto red_shoplocationsindex: combis){
        vector<int> true_locations;

        for (auto index:red_shoplocationsindex){
            true_locations.push_back(positions_vertex[index]);
        }

        vector<int> red_summary; red_summary.reserve(coffee_city.num_vertices);
        red_summary = finalizer(true_locations, coffee_city);
        vertex_painter(black_summary, red_summary, coffee_city);


        int red_count = coverage_calculator(coffee_city);

        for (auto true_loc:true_locations){
            cout << true_loc << " ";
        }
            cout << endl;
        coverage_printer(red_count, totaledge_weight);

        vertex_unpainter(coffee_city);
        //vertex_unpainter

    }





    /*

    vector<int> red_shops;
    for(int i = 0; i < number_red; i++){
        int red_shop;
        input >> red_shop;

        red_shops.push_back(red_shop);
    }

    vector<int> red_summary; red_summary.reserve(total_vertices);

    red_summary = finalizer(red_shops, coffee_city);

    vertex_painter(black_summary, red_summary, coffee_city);

    int red_count = coverage_calculator(coffee_city);
    coverage_printer(red_count, totaledge_weight);

    */

}
