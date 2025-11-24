// Lab 34 | Toma Dimov | COMSC 210 

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
#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const int SIZE = 9;

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
/*
    //Minimal spanning tree, Kruskal's Algorithm
    void MST(){
        int initial = 0;//lets start at the beginning
        vector<int> parent, rank;
        vector<Edge> tempList; //temp list so we don't modify the original
        copy(adjList.begin(),adjList.end(), back_inserter(tempList));
        //sort all edges in a non-decreasing order of their weight
        sort(tempList.begin(),tempList.end(),comparator);
        //traverse edges in sorted order
        int cost = 0, count = 0;
        for(auto &e : tempList){

            //make sure there is no cycle:

        }
        
        //pick the smallest edge
            //check if it forms a cycle with the spanning tree formed so far
                //no cycle? include this edge
                //else? discard it
        //repeat step two until there are v-1 edges in the spanning tree

    }
*/
};

void menu(){
    while(true){
        string input;
        cout<<"Bus Network menu:\n";
        cout<<"[1] Display Bus Stops and Routes\n";
        cout<<"[2] Test Passenger Route (BFS) \n";
        cout<<"[3] Test Passenger Route (DFS) \n";
        cout<<"[0] Exit\n";
        cout<<"Enter your choice: ";
        cin>>input;
        int result = stoi(input);
        switch (result)
        {
        case 0:
            return;
        case 1:
            cout<<
            BFS
        default:
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

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.BFS(0);
    graph.DFS(0);

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
    return 0;
}
