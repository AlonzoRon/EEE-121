#include<algorithm>
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

    vector<vector <pair<int, int> > > adjacency_list;


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

        adjacency_list.reserve(vertices);


    }


    void add_edge(int u, int v, int w){
        adjacency_list[u].push_back({v, w});
        adjacency_list[v].push_back({u, w});

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

int distance_calculator(int non_red, int red, Graph &G, int edge_weight){
    int non_red_dist, red_dist;
    int distance;

    non_red_dist = G.vertex_colors[non_red].second;
    red_dist = G.vertex_colors[red].second;
    cout << "non_red_dist: " << non_red_dist << "  red_dist: " << red_dist << endl;

    distance =  (((red_dist + non_red_dist + edge_weight) / 2) - non_red_dist);

    return distance;
}

int coverage_calculator(Graph &G, vector<vector<pair<int, int> > > &adjacency_list){
    int total_red = 0;


    //bool visited[G.num_vertices][G.num_vertices];
    //bool visited[G.num_vertices][G.num_vertices];
    bool visited[G.num_vertices][G.num_vertices];

    for (int i = 0; i < G.num_vertices; i++){
        for (int j = 0; j < G.num_vertices; j++){
            visited[i][j] = false;
        }
    }

    //vector<vector<bool > > visited;
    //visited.reserve(G.num_vertices);
    //for(int i = 0; i < G.num_vertices;d[i++){
    //    visited[i].reserve(G.num_vertices);
    //}
    //////
    for(int i = 0; i < G.num_vertices; i++){
        //cout << i << " vertex  Adjacentyehey: ";

        for(auto adjacent:adjacency_list[i]){
            cout << adjacent.first << " ";

            int dest = adjacent.first;
            int edge_weight = adjacent.second;
            cout << "current s/d: " << i << "->>" << dest << "edge_weight -->" << edge_weight <<  endl;

            color source_color = G.vertex_colors[i].first;
            color dest_color = G.vertex_colors[dest].first;

            if (visited[dest][i]){
                cout << i << ", " << dest << " has been visited" << endl;
                continue;
            }
            cout << "current s/d marked!!!!!!: " << i << "->>" << dest << endl;

            if (source_color == red){
                if(dest_color == red){
                    total_red += edge_weight;
                    cout << "source" << i << "   dest" << dest << "  added -->" << edge_weight << endl;
                }
                else if(dest_color == black){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(i, dest, G, edge_weight) << endl;
                }
                else if(dest_color == indifferent){
                    total_red += distance_calculator(i, dest, G, edge_weight);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(i, dest, G, edge_weight) << endl;
                }
            }
            else if (source_color == black){
                if(dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(dest, i, G, edge_weight) << endl;
                }
            }
            else if (source_color == indifferent){
                if(dest_color == red){
                    total_red += distance_calculator(dest, i, G, edge_weight);
                    cout << "source" << i << "   dest" << dest << "  added -->" <<  distance_calculator(dest, i, G, edge_weight) << endl;
                }
            }
            visited[i][dest] = true;
            visited[dest][i] = true;

        }
        cout << endl;
    }

    /*
    //////
    int total_red = 0;

    for(int i = 0; i < G.num_vertices; i++){
        for (auto destination:adjacency_list[i]){
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

    */

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

int city_evaluator(vector<int> red_shops, Graph coffee_city, vector <int> black_shops, int totaledge_weight, vector <vector<pair<int, int > > > &adjacency_list){
    //ifstream input("coffee_city.txt");
    //int n, m;
    //input >> n >> m;
//
    //int total_vertices = n;
//
    //cout << "new graph" << endl;
    //Graph coffee_city(total_vertices); // created the coffee city Graph
    //cout << "new graph" << endl;
    //int totaledge_weight = 0;
//
    //for(int i = 0; i < m; i++){
    //    int u, v, w;
    //    input >> u >> v >> w;
//
//
    //    coffee_city.add_edge(u, v, w * 2);
    //    totaledge_weight += w * 2;
    //    // we use w * 2 to prevent any problems with 0.5 for integers
    //}
//
    //int r, s;
    //int number_red, number_black;
    //input >> r >> s;
//
    //number_black = r;
    //number_red = s;
//
//
//
    //vector<int> black_shops;
    //for(int i = 0; i < number_black; i++){
    //    int black_shop;
    //    input >> black_shop;
//
    //    black_shops.push_back(black_shop);
    //}
//
    ////vector<int> red_shops;
    //for(int i = 0; i < number_red; i++){
    //    int red_shop;
    //    input >> red_shop;
//
    //    red_shops.push_back(red_shop);
    //}
    for(int i = 0; i < coffee_city.num_vertices; i++){
        cout << i << " vertex  Adjacent: ";

        for(auto adjacent:adjacency_list[i]){
            cout << adjacent.first << " ";
        }
        cout << endl;
    }


    cout << "ranbool" << endl;
    vector<int> black_summary; black_summary.reserve(coffee_city.num_vertices);
    vector<int> red_summary; red_summary.reserve(coffee_city.num_vertices);

    cout << "ranbool" << endl;
    black_summary = finalizer(black_shops, coffee_city);
    red_summary = finalizer(red_shops, coffee_city);

    cout << "ranbool" << endl;
    cout << "ran" << endl;
    vertex_painter(black_summary, red_summary, coffee_city);
    coffee_city.vertex_colors_printer();
    cout << "ran" << endl;

    int red_count = coverage_calculator(coffee_city, adjacency_list);
    cout << "ran" << endl;

    coverage_printer(red_count, totaledge_weight);



    return red_count;

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
    int num_vertices, m;
    input >> num_vertices >> m;

    vector<vector< pair <int, int> > > adjacency_list;
    adjacency_list.reserve(num_vertices);

    Graph coffee_city(num_vertices);

    int totaledge_weight = 0;
    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;

        coffee_city.add_edge(u, v, w * 2);
        cout << "added edge" << endl;
        totaledge_weight += w * 2;

        adjacency_list[u].push_back({v,w * 2});
        adjacency_list[v].push_back({u,w *2});
    }

    int r, s;
    int number_redwanted, number_black;
    input >> r >> s;

    number_black = r;
    number_redwanted = s;

    //int num_possiblepositions = num_vertices - number_black;
//
    //cout << num_possiblepositions << endl;
//
    //combinations_generator(num_possiblepositions, number_redwanted);


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

    cout << possible_positions << endl;

    vector< vector< int> > combis = combinations_generator(possible_positions, number_redwanted);

    //make a vector sized 0 - 13

    vector<int> positions_vertex;
    //fill this vector of only possible

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

    for(auto x: positions_vertex){
        cout << x << " ";
    }
    cout << endl;

//    for(auto red_shoplocationsindex: combis){
//        vector<int> true_locations;
//
//        for (auto index:red_shoplocationsindex){
//            true_locations.push_back(positions_vertex[index]);
//        }
//
//        //city_evaluator(true_locations);
//
//        for (auto true_loc:true_locations){
//            cout << true_loc << " ";
//        }
//        cout << endl;
//
//        input.clear();
//        input.seekg(0, ios::beg);
//    }

    input.close();
    input.clear();
    input.seekg(0, ios::beg);

    cout << coffee_city.num_vertices << endl;
    city_evaluator({6,8}, coffee_city, black_shops, totaledge_weight, adjacency_list);
    city_evaluator({0,1}, coffee_city, black_shops, totaledge_weight, adjacency_list);
    city_evaluator({0,2}, coffee_city, black_shops, totaledge_weight, adjacency_list);
    city_evaluator({0,3}, coffee_city, black_shops, totaledge_weight, adjacency_list);
    city_evaluator({0,4}, coffee_city, black_shops, totaledge_weight, adjacency_list);
    //city_evaluator({6,8}, coffee_city, black_shops, totaledge_weight, adjacency_list);

    //for(auto adjacency: coffee_city.adjacency_list){
    //    for(auto vertex: adjacency){
    //        cout<< adjacency.first << endl;
    //    }
    //}

    //cout << city_evaluator({0,1}, coffee_city, black_shops, totaledge_weight) << endl;
    //input.close();
    //input.clear();
    //input.seekg(0, ios::beg);
    //city_evaluator({0,1}, coffee_city, black_shops, totaledge_weight);

    //cout << adjacency_list[5].size() << endl;


    for(int i = 0; i < num_vertices; i++){
        cout << i << " vertex  Adjacent: ";

        for(auto adjacent:adjacency_list[i]){
            cout << adjacent.first << " ";
        }
        cout << endl;
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
