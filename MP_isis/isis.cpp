#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;

class Edge{
public:
    int source;
    int dest;
    int weight;

    Edge(int s, int d, int w){
        source = s;
        dest = d;
        weight = w;
    }

    void print_edge(){
        cout << "{ " << source << " " << dest <<  " "  << weight << " }" << endl;
    }
};

bool by_weight(const Edge& a, const Edge& b){
    return a.weight > b.weight;
}

bool inside(int x, vector<pair <int, int> > v){
    if (find(v.begin(), v.end(), x) != v.end()){
        return true;
    }
    return false;
}
vector<Edge> selector(vector<Edge> v_edge, int k){
    vector<Edge> return_vecedge;
    vector<pair<int, int> > past_list;
    //vector<bool> past_vertex;
    //past_vertex.reserve(k);

    //while(return_vecedge.size() < k){
        for(auto edge: v_edge){
            if(inside(edge.source, past_list) && inside(edge.dest, past_list)){
                continue;
            }
            else{
                return_vecedge.push_back(edge);
                past_list.push_back(edge.source);
                past_list.push_back(edge.dest);
                }
        }
    //}

    return return_vecedge;
}

    //for(int i = 1; i < k; i++){
    //
    //}
    //}

int main(){
    ifstream input("MP2.in");
    int n, m, k;
    input >> n >> k >> m;


    vector<Edge> Edgesforflights;
    vector<int> set;
    for(int i = 0; i < m; i++){
        int u, v, w;
        int threshold = k - 1;
        input >> u >> v >> w;

        if(u <= threshold && v <= threshold){
            Edge curr_edge = Edge(u, v, w);

            Edgesforflights.push_back(curr_edge);
        }
    }

    for(auto edge: Edgesforflights){
        edge.print_edge();
    }

    sort(Edgesforflights.begin(), Edgesforflights.end(), by_weight);

    cout << endl;

    for(auto edge: Edgesforflights){
        edge.print_edge();
    }

    vector<Edge> v_new = selector(Edgesforflights, k);

    cout << endl;
    for(auto edge: v_new){
        edge.print_edge();
    }


}
