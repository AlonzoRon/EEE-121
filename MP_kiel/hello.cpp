#include<bits/stdc++.h>
using namespace std;

const int inf = 1000000;

// iPair ==>  Integer Pair 
typedef pair<int, int> iPair; 
  
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // In a weighted graph, we need to store vertex 
    // and weight pair for every edge 
    list< pair<int, int> > *adj; 
  
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int u, int v, int w); 
  
    // prints shortest path from s 
    void shortestPath(int s); 
    vector<int> ownedshops;
    vector<int> enemyshops;
}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<iPair> [V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
} 
  
// Prints shortest paths from src to all other vertices 
vector<int> Graph::shortestPath(int src){ 
    // Create a priority queue to store vertices that 
    // are being preprocessed. This is weird syntax in C++. 
    // Refer below link for details of this syntax 
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/ 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(V, inf); 
  
    // Insert source itself in priority queue and initialize 
    // its distance as 0. 
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till priority queue becomes empty (or all 
      distances are not finalized) */
    while (!pq.empty()) 
    { 
        // The first vertex in pair is the minimum distance 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = pq.top().second; 
        pq.pop(); 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorted path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
  
    // Print shortest distances stored in dist[] 
 /*   printf("Vertex   Distance from Source\n");{
    for (int i = 0; i < V; ++i) 
	        printf("%d \t\t %d\n", i, dist[i]); 
	} */
	return dist;
  
    //function that sets the vertices as shops
  /*  void shopsetter(int own_shops, int enemy_shops){
        for(int i = 0; i < ownedshops.size(); i++){
            
            
        }
        
    }*/
    

    
};


int main(){
    ifstream file("coffee_city_small.txt");
    int n, m, r, s;           // n - number of vertices, m - number of edges
    file >> n >> m;
    
    Graph City(n);
    int V = 9;
    
    // read graph from file
    for(int i = 0; i < m; i++){
        int u, v, weight;
        file >> u >> v >> weight;
        City.addEdge(u, v, weight);
    }
    
    file >> r >> s;
    for (int i = 0; i < r; i++){
        int t;
        file >> t;
        City.ownedshops.push_back(t);
    }
    for (int i = 0; i < s; i++){
        int t;
        file >> t;
        City.enemyshops.push_back(t);
    }
    for(int i = 0; i < V; ++i){
    	vector<int> dist = City.shortestPath(5);
    	cout << i << " " << dist[i] << endl;
    } 
}

