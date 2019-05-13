#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

enum EdgeColor {black, red, indifferent};

class Edge{
public:
    int divisions;
    int red;
    int black;
    int indifferent;

    Edge(int subdivisions){
        divisions = subdivisions;
    }
};

class Graph{
public:
    int num_vertices;
    vector <vector <int> > adjacency_list;
    vector <vector <Edge> > edgematrix;

    Graph(int vertices){
        num_vertices = vertices;
        adjacency_list.reserve(vertices);

        edgematrix.reserve(vertices);

        for(int i = 0; i < vertices; i++){
            edgematrix[i].reserve(vertices);
        }
    }
    void add_edge(int u, int v, Edge e){
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);

        edgematrix[u][v] = e;
        edgematrix[v][u] = e;
    }
};

void add_red(vector <pair <int, int> > &red_list, Graph &G){
    for(auto pairing : red_list){
        int src = pairing.first;
        int dest = pairing.second;

        Edge &curr_edge = G.edgematrix[src][dest];
        Edge &othercurr_edge = G.edgematrix[dest][src];

        curr_edge.divisions -= 1;
        othercurr_edge.divisions -= 1;

        curr_edge.red += 1;
        othercurr_edge.red += 1;
    }

    red_list.clear();
    //for(int i = 0; i < red_list.size() + 1; i++){
    //    red_list.pop_back();
    //}
}


//bool visited_red[10000][10000];
void candidate_selector(int src, EdgeColor color, Graph &G,
     vector <pair <int, int> >  &past_edges,
     vector <pair<int, int> > &candidates){

    for(auto adjacent : G.adjacency_list[src]){
        Edge &curr_edge = G.edgematrix[src][adjacent];
        Edge &othercurr_edge = G.edgematrix[adjacent][src];

        //if(visited_red[src][adjacent]) continue;

        bool is_past = false;
        for (auto past : past_edges){
            int sourcey, destey;

            sourcey = past.first;
            destey = past.second;

            if(src == destey && adjacent == sourcey){
                is_past = true;
                break;
            }
        }

        if (is_past) continue;

        if(curr_edge.divisions != 0){
            // bool repeated = false;
            // for(auto pairing : candidates){
            //     int sorz, dezt;
            //     sorz = pairing.first;
            //     dezt = pairing.second;
            //     if(sorz == src && dezt == adjacent){
            //             repeated = true;
            //             break;
            //     }
            // }
            // if(repeated) continue;
            candidates.push_back({src, adjacent});
        }

        if(color == red){
            if(curr_edge.divisions == 0 && curr_edge.black > 0){ // meaning with black
                continue;
            }
            else if(curr_edge.divisions == 0 && curr_edge.black == 0){ // meaning all red
                //visited_red[src][adjacent] = true;
                //visited_red[adjacent][src] = true;

                pair <int, int> completed_srcadj = {src, adjacent};
                cout << "completed edge: " << src << " ---> " << adjacent <<  endl;
                //past_edges.push_back(src);
                past_edges.push_back(completed_srcadj);

                candidate_selector(adjacent,color, G, past_edges, candidates);

            }

        }

        else if(color == black){

        }


    }

}

int coverage_counter_red(Graph &G, int n){
    int num_red = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            num_red += G.edgematrix[i][j].red;
        }
    }

    return num_red;
}
int coverage_counter(Graph &G, int n){
    int no_subdi = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            no_subdi += G.edgematrix[i][j].divisions;
        }
    }

    return no_subdi;
}
int main(){
    ifstream input("coffee_city_4x4.txt");
    int n, m;
    input >> n >> m;

    Graph c_city(n);

    for(int i = 0; i < m; i++){
        int u, v, w;
        input >> u >> v >> w;

        Edge e(w * 2);

        c_city.add_edge(u, v, e);

        // do something about u, v, w
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
    /////
    int initial_coverage = coverage_counter(c_city, n);
    cout << coverage_counter(c_city, n) << endl;
    cout << endl;
    ////

    vector <pair <int, int> > candidates;
    vector<pair<int, int> >  red_past_edges;
    for(int i = 0; i < 11; i++){
        candidate_selector(1, red, c_city, red_past_edges, candidates);

        for (auto pairing : candidates){
            cout << pairing.first << "---->" << pairing.second << "   ";
        }
        cout << endl;

        add_red(candidates, c_city);
}
    ////////
    int redcov = coverage_counter_red(c_city, n);
    double percent = (double)redcov/(double)initial_coverage * 100;
    //initial_coverage * 100;
    cout << percent << "%" << endl;

    candidates.clear();
    red_past_edges.clear();
}
