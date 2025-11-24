// Lab 34 | Toma Dimov | COMSC 210 
#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const int SIZE = 9, INTMAX = 90000;

struct Edge {
    int src, dest, weight;
    public:
    void set_weight(int w){weight = w;}
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

bool comparator(vector<int> &a,vector<int> &b){
   return a[2] < b[2]; 
}

class Graph {
private:
  // Union-Find helper functions for Kruskal's algorithm
    int find(vector<int> &parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]); // Path compression
        }
        return parent[i];
    }
    
    void unionSets(vector<int> &parent, vector<int> &rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    void dfs(int u, vector<bool> &visited) {
        visited[u] = true;
        for (auto &neighbor : adjList[u]) {
            int v = neighbor.first;
            if (!visited[v]) {
                dfs(v, visited);
            }
        }
    }

public:
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

    vector<int> shortestPath(int startNode) {
        // Create a priority queue (min-heap) to store vertices
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        
        // Create a vector for distances and initialize all distances as infinite (INT_MAX)
        vector<int> dist(SIZE, INTMAX);
        
        // Insert source itself in priority queue and initialize its distance as 0
        pq.push(make_pair(0, startNode));
        dist[startNode] = 0;
        
        // Looping till priority queue becomes empty (or all distances are finalized)
        while (!pq.empty()) {
            // The first vertex in pair is the minimum distance vertex
            // extract it from priority queue. Vertex label is stored in second of pair
            int u = pq.top().second;
            pq.pop();
            
            // Get all adjacent vertices of u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                // If there is a shorter path to v through u
                if (dist[v] > dist[u] + weight) {
                    // Update distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;
    }

    // Utility function to print shortest paths
    void printShortestPaths(int startNode) {
        vector<int> distances = shortestPath(startNode);
        
        cout << "Shortest distances from Bus Stop " << startNode << ":\n";
        for (int i = 0; i < SIZE; i++) {
            if (distances[i] == INTMAX) {
                cout << "Bus Stop "<<startNode<<" -> " << i << " : Unreachable\n";
            } else {
                cout << "Bus Stop "<<startNode<<" -> "  << i << " : " << distances[i] <<" minutes."<< "\n";
            }
        }
    }

    vector<Edge> kruskalMST() {
        vector<Edge> mst;
        vector<Edge> allEdges;
        
        // Collect all edges from adjacency list
        for (int u = 0; u < SIZE; u++) {
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                // To avoid duplicates in undirected graph
                if (u < v) {
                    Edge edge;
                    edge.src = u;
                    edge.dest = v;
                    edge.weight = weight;
                    allEdges.push_back(edge);
                }
            }
        }
        // Sort edges by weight
        sort(allEdges.begin(), allEdges.end(), 
             [](const Edge &a, const Edge &b) { return a.weight < b.weight; });
        // Union-Find data structure
        vector<int> parent(SIZE);
        vector<int> rank(SIZE, 0);
        // Initialize Union-Find
        for (int i = 0; i < SIZE; i++) {
            parent[i] = i;
        }
        // Process edges in sorted order
        for (auto &edge : allEdges) {
            int rootSrc = find(parent, edge.src);
            int rootDest = find(parent, edge.dest);
            
            // If including this edge doesn't cause cycle
            if (rootSrc != rootDest) {
                mst.push_back(edge);
                unionSets(parent, rank, rootSrc, rootDest);
            }
            
            // Stop when we have V-1 edges
            if (mst.size() == SIZE - 1) break;
        }
        return mst;
    }

    // Utility function to print MST
    void printMST(const vector<Edge> &mst, const string &algorithm) {
        cout << algorithm << " Minimum Spanning Tree:\n";
        int totalWeight = 0;
        
        for (const auto &edge : mst) {
            cout <<"Bus Stop from "<< edge.src << " to " << edge.dest << " with travel time:  " << edge.weight << " minutes. \n";
            totalWeight += edge.weight;
        }
        
        cout << "Total weight: " << totalWeight << "\n\n";
    }

    // Function to get total weight of MST
    int getMSTWeight(const vector<Edge> &mst) {
        int totalWeight = 0;
        for (const auto &edge : mst) {
            totalWeight += edge.weight;
        }
        return totalWeight;
    }

    // Check if graph is connected (prerequisite for spanning tree)
    bool isConnected() {
        vector<bool> visited(SIZE, false);
        dfs(0, visited);
        
        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "COUNTY BUS NETWORK:" << endl<<"===========================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout <<"Stop "<< i << " has bus route to:\n";
            for (Pair v : adjList[i]){
                cout << "\t -> Stop" <<setw(2)<< v.first << " (Time: " << v.second << " minutes.)\n";
            }
        }
    }

    //Breadth First Search
    void BFS(int initial){
        cout<<"Test Passenger takes a random route via Breadth First Algorithm until reaching every stop, starting from Stop "<< initial<<":\n";
        cout<<"===========================================\n";
        queue<int> next;//start by declaring a queue to keep track of the next location to visit:
        vector<bool> visited(adjList.size(),false);
        //initial visit
        visited[initial] = true;
        next.push(initial);
        //iteration
        while(next.size()>0){ //while not empty
            //check who is next.
            int x = next.front();
            cout<<"Passenger arrives at Stop "<< x<<":\n";
            next.pop();

            for(Pair v: adjList[x]){
                int z = v.first;
                if(!visited[z]){ //has it been visited?
                    cout<<"\t->Passenger could catch a bus to Stop "<<z<<endl;
                    next.push(z);
                    visited[z]=true;
                }
            }
        }
        cout<<endl;
    }

    //Depth First Search
    void DFS(int initial){
        cout<<"Test Passenger takes a random route via Depth First Algorithm until reaching every stop, starting from Stop "<< initial<<":\n";
        cout<<"===========================================\n";
        stack<int> next; //start by declaring a stack
        vector<bool> visited(adjList.size(),false);
        //initial visit
        visited[initial] = true;
        next.push(initial);
        //iteration
        while(next.size()>0){ //while not empty
            int x = next.top();
            cout<<"Passenger arrives at Stop "<< x<<":\n";
            next.pop();

            for(Pair v: adjList[x]){
                int z = v.first;
                if(!visited[z]){ //has it been visited?
                    cout<<"\t->Passenger could catch a bus to Stop "<<z<<endl;
                    next.push(z);
                    visited[z]=true;
                }
            }
        }
    }
};

void menu(Graph graph){
    while(true){
        string input;
        cout<<"Bus Network menu:\n";
        cout<<"[1] Display Bus Stops and Routes. \n";
        cout<<"[2] Test Passenger Route (BFS). \n";
        cout<<"[3] Test Passenger Route (DFS). \n";
        cout<<"[4] Display Shortest Path from a Given Stop. \n";
        cout<<"[5] Print Spanning Tree for Bus Network.\n";
        cout<<"[0] Exit. \n";
        cout<<"Enter your choice: ";
        cin>>input;
        int result = stoi(input);
        switch (result)
        {
        case 0:
            return;
        case 1:{
            graph.printGraph();
            break;
        }
        case 2:{
            string input2;
            cout<<"Starting stop: ";
            cin>>input2;
            int initial = stoi(input2);
            graph.BFS(initial);
            break;
        }
        case 3:{
            string input2;
            cout<<"Starting stop: ";
            cin>>input2;
            int initial = stoi(input2);
            graph.DFS(initial);
            break;
        }
        case 4:{
            string input2;
            cout<<"Starting stop: ";
            cin>>input2;
            int initial = stoi(input2);
            graph.printShortestPaths(initial);
            break;
        }
        case 5:{
            vector<Edge> kruskalTree = graph.kruskalMST();
            graph.printMST(kruskalTree,"[Kruskal Algorithm]");
            break;
        }
        default:
            cout<<"Not a valid option, try again.\n";
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5},{7,8,1},{8,3,4}
    };

    // Creates graph
    Graph graph(edges);

    //change the graph by deleting two nodes and adding six new ones. change the weights
    edges.pop_back();
    edges.pop_back();
    edges[1].set_weight(4);
    edges[6].set_weight(12);
    edges.push_back({7,8,1});
    edges.push_back({0,6,12});
    edges.push_back({3,5,9});
    edges.push_back({4,6,20});
    edges.push_back({1,4,12});
    edges.push_back({3,7,18});
    menu(graph);
    return 0;
}
