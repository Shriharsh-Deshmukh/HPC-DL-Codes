#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

// Function to perform BFS and return the traversal order
vector<int> bfsOfGraph(int V, vector<int> adj[], int startNode) 
{

    // Array to keep track of visited nodes, 1-based index
    int vis[V + 1] = {0};  
    vis[startNode] = 1;  
    queue<int> q;
    q.push(startNode); 
    vector<int> bfs; 

    // Iterate until the queue is empty
    while(!q.empty()) {
        int node = q.front(); 
        q.pop(); 
        bfs.push_back(node); 

        // Parallelize the neighbor traversal using OpenMP
        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {
            int it = adj[node][i];
            // If the neighbor hasn't been visited, store it in the queue and mark as visited
            if (!vis[it]) {
                #pragma omp critical
                {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
    }
    return bfs; 
}

// // Function to add an edge to the graph
// void addEdge(vector <int> adj[], int u, int v) {
//     adj[u].push_back(v);
//     adj[v].push_back(u);
// }

// Function to print the result of BFS traversal
void printAns(vector <int> &ans) {
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector <int> adj[V + 1];  // We need V+1 for 1-based indexing
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int startNode;
    cout << "Enter the starting node for BFS (1-based index): ";
    cin >> startNode;

    // Perform BFS and store the result
    vector <int> ans = bfsOfGraph(V, adj, startNode);
    
    // Print the result
    printAns(ans);

    return 0;
}
