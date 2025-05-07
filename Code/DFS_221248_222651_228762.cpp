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

// DFS Traversal
void dfs(int start) {
    unordered_map<int, bool> visited;
    stack<int> s;
    s.push(start);
    ofstream trace("dfs_trace.txt");

    while (!s.empty()) {
        int u = s.top(); s.pop();
        if (!visited[u]) {
            visited[u] = true;
            trace << "Visited: " << u << "\n";
            for (Edge e : graph[u]) {
                if (!visited[e.to]) s.push(e.to);
            }
        }
    }
}

int main() {
    loadGraph("bitcoin_weighted_edges.txt", true);
    int source = 1; // Choose appropriate source node

    dfs(source);

    return 0;
}
