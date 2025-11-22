// Lab 34 | Toma Dimov | COMSC 210 
////STEP 1
//through the prompt engineering, transform the code by adding DFS and BFS
//write the driver program to excercies code
//commit: "Step 1 Complete"

/////STEP 2
//Change the graph by deletign at least two nodes and adding at least six nodes, change the weights as well.
//Step 2 complete commit

///STEP 3
//Through expert prompt engineering, wrap an application around this new graph. 
//It should be some real-world example that is represented by your graph.

//STEP 4
//Through prompt engineering, add code to procide the shortest path through your graph.
//Ste4 complete

//STEP 5
//Through prompt engineering, add code to provide the minimum spanning tree of your graph.

//Step 6
//Place a menu with all funcionality.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    void BFS();
    void DFS();
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    //Breadth First Search
    void BFS(){
        queue<Pair> to_visit;//start by declaring a queue to keep track of the next location to visit:
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                to_visit.push(v);
            cout << endl;
        adjList[0]  ;  //default to zero, the start
        while(to_visit){
            
        }
        
        cout<<
            //start by marking the source node as visited.
        cout<<"BFS starting from vertex 0:\n";
            cout << v.first;
    }

    void DFS(){
        
        cout<<"BFS starting from vertex 0:\n";

    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    return 0;
}

