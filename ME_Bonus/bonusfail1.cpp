#include<bits/stdc++.h>
using namespace std;

/*
    File description:
     - first line: n = number of students (also equal to the number of teachers), m = number of edges
     - next m lines: a student and a teacher forming an edge for possible matching

    In the file:
     - students are numbered 0, 1, 2, ..., n - 1
     - teachers are numbered n, n + 1, n + 2, ..., 2*n - 1
    Hence, the graph has 2n vertices and m edges.

    Outline of bonus exercise (see code below for the exact location)
     - (1 point) Check if a student is unmatched.
     - (2 points) Find an unmatched teacher found using the alternating path algorithm.
     - (2 points) Flip colors of all edges in an alternating path
     - (1 point) Print the resulting matching
*/

enum EdgeColor{black, white, not_an_edge};

class Graph{
private:
    int num_vertices;
    vector<vector<int> > __adj;

public:
    Graph(int n) : num_vertices(n), __adj(n){}

    int vertex_count(){
        return num_vertices;
    }

    void add_edge(int u, int v){
        __adj[u].push_back(v);
    }

    vector<int>& adj(int v){
        return __adj[v];
    }
};


int main(){
    int n, m;
    ifstream file("bipartite_graph.txt");

    file >> n >> m;

    Graph G(2 * n);

    EdgeColor edge[2 * n][2 * n];

    // Initialize edge[][] matrix
    for(int i = 0; i < 2 * n; i++){
        for(int j = 0; j < 2 * n; j++){
            edge[i][j] = not_an_edge;
            edge[j][i] = not_an_edge;
        }
    }

    // Read edges
    for(int i = 0; i < m; i++){
        int u, v;
        file >> u >> v;

        G.add_edge(u, v);
        G.add_edge(v, u);
    }


    // Color all edges white. That is, no student has been matched to a teacher (for now).
    for(int i = 0; i < 2 * n; i++){
        for(auto j : G.adj(i)){
            edge[i][j] = white;
            edge[j][i] = white;
        }
    }

    while(true){
        bool improved_matching = false;

        for(int student = 0; student < n; student++){
            bool is_matched = true;

            /* (1 point) A student is unmatched if all outgoing edges are white (or not_an_edge).
                         Use a for-loop to check if "student" is matched. Upon detection of a black outgoing edge, set is_matched to false.
            */

            for(auto teacher : G.adj(student)){
                if (edge[student][teacher] == black || edge[teacher][student] == black){
                    is_matched = false;
                    break;
                }
            }

            /*
                Insert code for is_matched.
            */

            // Ignore unmatched students
            if (!is_matched) continue;

            int dist[2 * n], pred[2 * n];
            queue<int> Q;

            // Initialize dist and pred
            for(int i = 0; i < 2 * n; i++){
                dist[i] = -1;
                pred[i] = -1;
            }

            // Push all students into a queue, and for each student i, set dist[i] = 0, and pred[i] = i.
            Q.push(student);
            dist[student] = 0;
            pred[student] = student;

            // Find an alternating path which starts at an unmatched student, and ends at an unmatched teacher
            while(!Q.empty()){
                int curr = Q.front();
                Q.pop();

                for(auto nxt : G.adj(curr)){
                    if (dist[nxt] != -1) continue;

                    if (dist[curr] % 2 == 0){   // if true, then nxt is a teacher
                        if (edge[curr][nxt] == white){
                            Q.push(nxt);
                            dist[nxt] = dist[curr] + 1;
                            pred[nxt] = curr;
                        }
                    }
                    else{
                        if (edge[curr][nxt] == black){
                            Q.push(nxt);
                            dist[nxt] = dist[curr] + 1;
                            pred[nxt] = curr;
                        }
                    }
                }
            }
            cout << endl;
            // (2 points) Find an *unmatched* teacher with a predecessor. Save it to unmatched_teacher.
            int unmatched_teacher = -1;

            for(int i = n; i < 2 * n; i++){ // Teachers are numbered: n, n + 1, n + 2, ..., 2n - 1
                /*
                    Fill in the code
                */
                bool unmatched = true;
                for(auto pupil:G.adj(n)){
                    if(edge[n][pupil] != white || edge[pupil][n] != white){
                        unmatched = false;
                    }
                }

                if(pred[n] != -1 && unmatched == true) unmatched_teacher = n;

            }

            // If no unmatched_teacher is found, try another student.
            if (unmatched_teacher == -1){
                continue;
            }
            else{
                improved_matching = true;
            }

            /*  (2 points)
                Starting from unmatched_teacher, use the pred[] array to flip the colors of edges from "student" to "unmatched_teacher"

                Example:
                  If the old path is (student) --> (some teacher) ==> (some student) --> (some teacher) ==> (some student) --> unmatched_teacher,
                then the new path is (student) ==> (some teacher) --> (some student) ==> (some teacher) --> (some student) ==> unmatched_teacher,

                where --> denotes a white edge, and ==> denotes a black edge.

                Don't forget: edges in this graph are bidirectional!
            */

            int v = unmatched_teacher;
            cout << "unmatched teacher" << v << endl;
            while(v != pred[v]){
                int previous = pred[v];

                if(edge[v][previous] == white || edge[previous][v] == white){
                    edge[v][previous] = black;
                    edge[previous][v] = black;
                }
                else if(edge[v][previous] == black || edge[previous][v] == black){
                    edge[v][previous] = white;
                    edge[previous][v] = white;
                }
                /*
                    Fill in the code.

                    Again, don't forget: edges in this graph are bidirectional!
                */
                v = pred[v];
            }

        //for(int i = 0; i < 2*n; i++){
        //    cout << i << " ---- previous --> " << pred[i] << endl;
        //}

        }


        if (!improved_matching) break;

    }

    for(int student = 0; student < n; student++){
        for(int teacher = n; teacher < n * 2; teacher++){
            // if(edge[student][teacher] == black){
            //     cout << student << " <--> " << teacher << endl;
            cout << "student "  << student;
            cout << " -- teacher "  << teacher;

            if (edge[student][teacher] == white){
                cout << "-->white" << endl;
            }

            else if (edge[student][teacher] == black){
                cout << "-->black" << endl;
            }

            else cout << "-->not black or white" << endl;

        }
    }


    /*
        (1 point)
        Print the resulting matching.

        Expected output:
        0 <--> 8
        1 <--> 5
        2 <--> 7
        3 <--> 6
        4 <--> 9
    */

}
