// C++ implementations for CS-2009 project
// Algorithms: Prim's MST, Kruskal's MST, Diameter of Graph, Cycle Detection

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <set>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

unordered_map<int, vector<pair<int, int>>> adj;
vector<Edge> allEdges;
set<int> nodes;

void loadGraph(const string& filename, bool directed = true) {
    ifstream file(filename);
    int u, v, w;
    while (file >> u >> v >> w) {
        adj[u].push_back({v, w});
        allEdges.push_back({u, v, w});
        nodes.insert(u);
        nodes.insert(v);
        if (!directed) adj[v].push_back({u, w});
    }
}

// Cycle Detection using DFS
bool dfsCycle(int u, int parent, unordered_map<int, bool>& visited) {
    visited[u] = true;
    for (auto [v, _] : adj[u]) {
        if (!visited[v]) {
            if (dfsCycle(v, u, visited)) return true;
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}

void detectCycle() {
    unordered_map<int, bool> visited;
    bool hasCycle = false;
    for (int node : nodes) {
        if (!visited[node] && dfsCycle(node, -1, visited)) {
            hasCycle = true;
            break;
        }
    }
    ofstream out("../Results/cycle_detection.txt");
    out << (hasCycle ? "Cycle found" : "No cycle detected") << endl;
}

int main() {
    loadGraph("../Dataset/bitcoin_weighted_edges.txt", false); // Undirected for MST and cycle


    detectCycle();

    return 0;
}
