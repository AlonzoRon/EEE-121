#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
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

vector <int> printLevels(Graph &G, int src){
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
//    cout << "Nodes"
//		<< " "
//		<< "Level" << endl;
//	for (int i = 0; i < G.num_vertices; i++)
//		cout << " " << i << " --> " << level[i] << endl;

    for(int i = 0; i < G.num_vertices; i++){
        return_vector.push_back(level[i]);

    }
    return return_vector;
}

vector <vector<pair<int, int> > > shop_expansionreport(vector <int> levels, Graph &G){
    vector <vector<pair <int, int> > > report;



    int highest = -1;
    for(auto level:levels){
        if(level > highest) highest = level;
    }
    cout << highest << endl;

    for(int i = 0; i < highest; i++){
        vector<pair<int,int> > per_leveltraversal;

        if(i == 0){
            for(int i = 0; i < G.num_vertices; i++){
                pair <int, int> layer0;

                if(levels[i] == 0){

                }
            }
        }
    }









    return report;
};

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

    vector <vector <vector <pair <int, int> > > >red_masterlist; //shops indexed by 0 1 2
    vector <vector <vector <pair <int, int> > > >black_masterlist;
    //red_masterlist.reserve(10000);
    //black_masterlist.reserve(10000);

    for(auto red: red_shops){
        vector <int> curr_levels = printLevels(coffee_city, red);
        vector <vector<pair<int, int> > > currshop_expansionreport;
        currshop_expansionreport = shop_expansionreport(curr_levels, coffee_city);
    }








//        vector <vector <pair <int, int> > > shop_expansionreport;
//
//        vector <int> levels;
//        levels = printLevels(coffee_city, red);
//
//        int highest = -1;
//        for(auto level:levels){
//            //cout << level << endl;
//            if (level > highest) highest = level;
//        }
//
//        cout << highest << endl;
//
//        for(int i = 0; i < highest; i++){
//            vector <pair <int, int> >   pairings_perlevel;
//
//            for (int i = 0; i < coffee_city.num_vertices; i ++){
//
//            }
//        }

        //get highest possible levels






    // printLevels(coffee_city, 1);
    // goal now is to produce correct layered traversal vector vector of pair<int>


}
