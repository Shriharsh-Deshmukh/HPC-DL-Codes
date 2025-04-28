#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

void parallelDFS(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> s;

    s.push(start);

    cout << "DFS Traversal:" << endl;

    while (!s.empty()) {
        int current;

        #pragma omp critical
        {
            if (!s.empty()) {
                current = s.top();
                s.pop();
            }
        }

        if (!visited[current]) {
            visited[current] = true;
            cout << current << "\t";

            // Push neighbors in reverse order for proper DFS
            #pragma omp parallel for
            for (int i = graph[current].size() - 1; i >= 0; i--) {
                int neighbor = graph[current][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        s.push(neighbor);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int n, e, start;
    cout << "Enter number of nodes, edges, and the starting node: ";
    cin >> n >> e >> start;

    vector<vector<int>> adj(n + 1); // ✅ Graph size n+1

    cout << "Enter pairs of connected edges (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    parallelDFS(adj, start);
}
