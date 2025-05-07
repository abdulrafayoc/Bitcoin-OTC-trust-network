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

// Bellman-Ford Algorithm
void bellmanFord(int src) {
    unordered_map<int, int> dist;
    for (int node : nodes) dist[node] = INF;
    dist[src] = 0;
    int N = nodes.size();

    for (int i = 1; i <= N - 1; i++) {
        for (auto [u, edges] : graph) {
            for (Edge e : edges) {
                if (dist[u] != INF && dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                }
            }
        }
    }

    ofstream out("bellmanford_result.txt");
    for (auto [node, d] : dist)
        out << src << " -> " << node << ": " << d << "\n";
}



int main() {
    loadGraph("bitcoin_weighted_edges.txt", true);
    int source = 1; // Choose appropriate source node

    auto start = chrono::high_resolution_clock::now();
    bellmanFord(source);
    auto end = chrono::high_resolution_clock::now();
    cout << "Bellman-Ford Time: " << chrono::duration<double>(end - start).count() << "s\n";


    return 0;
}
