#include<algorithm>
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<cmath>
using namespace std;


int inf = 10000000;
// "color" data type used to "paint" vertices and edges
enum color{black, red, indifferent, no_canvas, blank_canvas};

// edge class containing the edge_color
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
    list<pair<int, int> > *adj; // adjacency_list for dijkstra
    vector<vector <Edge> > color_matrix;
    vector<pair <color, int> > vertex_colors;

    Graph(int vertices){ // constructor
        num_vertices = vertices;
        adj = new list <pair<int, int> > [vertices];

        color_matrix.reserve(vertices);
        for(int i = 0; i < vertices; i++){
            color_matrix[i].reserve(vertices);
        }
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
        return dist;
    }

};

// converts the multi_list of all dist[] arrays to one summary array (gets the lowest val)
// [0, 2, 5, 0 ,8] vs. [1, 2, 3, 4, 5] returns: [0, 2, 3, 0, 5]
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

// this functions "paints" the vertices which will later be compared
void vertex_painter(vector<int> black_list, vector<int> red_list, Graph &G){
    for(int i = 0; i < G.num_vertices; i++){
        if(red_list[i] < black_list[i]){
            G.vertex_colors.push_back({red, red_list[i]});
        }
        else if(black_list[i] < red_list[i]){
            G.vertex_colors.push_back({black, black_list[i]});
        }
        else if(black_list[i] == red_list[i]){
            G.vertex_colors.push_back({indifferent, red_list[i]});
        }
    }
}

// this is a supplementary function to coverage_calculator
int distance_calculator(int non_red, int red, Graph &G, int edge_weight){
    int non_red_dist, red_dist;
    int distance;

    non_red_dist = G.vertex_colors[non_red].second;
    red_dist = G.vertex_colors[red].second;

    distance =  (((red_dist + non_red_dist + edge_weight) / 2) - non_red_dist);

    return distance;
}

// this function uses the painted vertices to actually count the number of red coverage
int coverage_calculator(Graph &G, vector<vector<pair<int, int> > > &adjacency_list){
    int total_red = 0;

    bool visited[G.num_vertices][G.num_vertices];

    for (int i = 0; i < G.num_vertices; i++){
        for (int j = 0; j < G.num_vertices; j++){
            visited[i][j] = false;
        }
    }
    for(int i = 0; i < G.num_vertices; i++){
        for(auto adjacent:adjacency_list[i]){

            int dest = adjacent.first;
            int edge_weight = adjacent.second;

            color source_color = G.vertex_colors[i].first;
            color dest_color = G.vertex_colors[dest].first;

            if (visited[dest][i]){
                continue;
            }

            if (source_color == red){
                if(dest_color == red){
                    total_red += edge_weight;
                }
                else if(dest_color == black){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                }
                else if(dest_color == indifferent){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                }
            }
            else if (source_color == black){
                if(dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                }
            }
            else if (source_color == indifferent){
                if(dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                }
            }
            visited[i][dest] = true;
            visited[dest][i] = true;
        }
    }

    return total_red;
}

// is basically a pretty print of the percentage
void coverage_printer(int num_red, int edges){
    double coverage;

    coverage = (double) num_red / (double) edges;

    coverage *= 10000;
    coverage = round(coverage);
    coverage /= 100;

    cout << coverage << "% coverage." << endl;
}

// this function is responsible for combining all the functions above together
int city_evaluator(vector<int> red_shops, Graph coffee_city, vector <int> black_shops,
                   int totaledge_weight, vector <vector<pair<int, int > > > &adjacency_list){

    // from all the shortest path arrays of all black shops, summarize all of them
    // into only one black and one red array
    vector<int> black_summary; black_summary.reserve(coffee_city.num_vertices);
    vector<int> red_summary; red_summary.reserve(coffee_city.num_vertices);
    black_summary = finalizer(black_shops, coffee_city);
    red_summary = finalizer(red_shops, coffee_city);

    // paint them accordingly using the created summary arrays
    vertex_painter(black_summary, red_summary, coffee_city);

    // calculate the coverage for this iteration, then return the value
    int red_count = coverage_calculator(coffee_city, adjacency_list);
    return red_count;

}
// this function generates all the index combinations for the possible positions
// for the red shops in subtask_2 which implements an exhaustive search.
vector<vector<int> > combinations_generator(int possible_positions, int red_shopnumber){
    vector<vector<int> > megalist;

    vector<bool> v(possible_positions);
    fill(v.begin(), v.begin() + red_shopnumber, true);

    do{
        vector<int> current;
        for(int i =0; i < possible_positions; i++){
            if (v[i]){
                // cout << i << " ";
                current.push_back(i);
            }
        }
        megalist.push_back(current);
        // cout << endl;
    } while(prev_permutation(v.begin(), v.end()));

    return megalist;
}

int main(){
    ifstream input("coffee_city_b-large.txt");
    int num_vertices, m;
    input >> num_vertices >> m;

    // create an adjacency list here
    vector<vector< pair <int, int> > > adjacency_list;
    adjacency_list.reserve(num_vertices);

    Graph coffee_city(num_vertices);

    int totaledge_weight = 0;
    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;

        coffee_city.add_edge(u, v, w * 2);
        totaledge_weight += w * 2;

        adjacency_list[u].push_back({v,w * 2});
        adjacency_list[v].push_back({u,w *2});
    }

    int r, s;
    int number_redwanted, number_black;
    input >> r >> s;

    number_black = r;
    number_redwanted = s;

    vector<int> black_shops;
    for(int i = 0; i < number_black; i++){
        int black_shop;
        input >> black_shop;

        black_shops.push_back(black_shop);
    }

    // this is the part when we count the number of available shop_locations
    // and generate ALL possible combinations of n(available slots) container
    //then iterate and compare the values and get the highest one

    number_redwanted = s;
    int possible_positions = num_vertices - number_black;
    vector<int> positions_vertex; // a vector containing the possible_positions

    for(int i = 0; i < num_vertices; i++){
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


    vector< vector< int> > combis = combinations_generator(possible_positions, number_redwanted);
    vector<int> optimal_positions;
    int max = -100;
    for(auto red_shoplocationsindex: combis){
        vector<int> true_locations;

        // function above checks the positions vertex and puts the true and correct
        // vertices of red to be placed inside true_locations vector
        for (auto index:red_shoplocationsindex){
            true_locations.push_back(positions_vertex[index]);
        }

        // inserts true_locations to city_evaluator function
        int red_cov = city_evaluator(true_locations, coffee_city, black_shops, totaledge_weight, adjacency_list);

        if(red_cov > max){
            max = red_cov;
            optimal_positions = true_locations;
        }


    }

    // this part just prints the output
    cout << "Install coffee shops at junctions: ";
    int i = 0;
    for(auto position:optimal_positions){
        cout << position;
        if (i != optimal_positions.size() - 1){
            cout << ", ";
        }
        i++;
    }
    cout << endl;
    coverage_printer(max, totaledge_weight);

}
