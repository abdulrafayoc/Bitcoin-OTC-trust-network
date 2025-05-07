// C++ implementations for CS-2009 project based on soc-sign-bitcoinotc dataset
// Algorithms: Dijkstra, Bellman-Ford, Prim, Kruskal, BFS, DFS, Diameter, Cycle Detection

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

const int INF = numeric_limits<int>::max();

// Graph representation using adjacency list
struct Edge {
    int to;
    int weight;
};

unordered_map<int, vector<Edge>> graph;
set<int> nodes;

void loadGraph(const string& filename, bool directed = true) {
    ifstream file(filename);
    int u, v, w;
    while (file >> u >> v >> w) {
        graph[u].push_back({v, w});
        nodes.insert(u);
        nodes.insert(v);
        if (!directed) graph[v].push_back({u, w});
    }
}

// BFS Traversal
void bfs(int start) {
    unordered_map<int, bool> visited;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    ofstream trace("bfs_trace.txt");

    while (!q.empty()) {
        int u = q.front(); q.pop();
        trace << "Visited: " << u << "\n";
        for (Edge e : graph[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
}


int main() {
    loadGraph("bitcoin_weighted_edges.txt", true);
    int source = 1; // Choose appropriate source node

    bfs(source);


    return 0;
}
