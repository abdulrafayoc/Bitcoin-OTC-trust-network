// C++ implementations for CS-2009 project based on soc-sign-bitcoinotc dataset
// Algorithm: Bellman-Ford
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

struct Edge {
    int to;
    int weight;
};

unordered_map<int, vector<Edge>> graph;
set<int> nodes;

bool loadGraph(const string& filename, bool directed = true) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        return false;
    }

    int u, v, w;
    while (file >> u >> v >> w) {
        graph[u].push_back({v, w});
        nodes.insert(u);
        nodes.insert(v);
        if (!directed) graph[v].push_back({u, w});
    }

    return true;
}

void bellmanFord(int src, const string& outputPath, const string& tracePath) {
    unordered_map<int, int> dist;
    for (int node : nodes) dist[node] = INF;
    dist[src] = 0;

    ofstream trace(tracePath);
    if (!trace.is_open()) {
        cerr << "Error: Could not write to trace file.\n";
        return;
    }

    int V = nodes.size();
    trace << "Start Bellman-Ford from node " << src << "\n";

    for (int i = 1; i < V; ++i) {
        trace << "Iteration " << i << ":\n";
        for (const auto& [u, edges] : graph) {
            for (const Edge& e : edges) {
                trace << "  Checking edge " << u << " -> " << e.to << " (weight=" << e.weight << ")\n";
                if (dist[u] != INF && dist[u] + e.weight < dist[e.to]) {
                    int oldDist = dist[e.to];
                    dist[e.to] = dist[u] + e.weight;
                    trace << "    Relaxed: dist[" << e.to << "] = " << oldDist
                          << " -> " << dist[e.to] << "\n";
                }
            }
        }
    }

    // Negative-weight cycle detection
    for (const auto& [u, edges] : graph) {
        for (const Edge& e : edges) {
            if (dist[u] != INF && dist[u] + e.weight < dist[e.to]) {
                trace << "Negative cycle detected on edge " << u << " -> " << e.to << "\n";
                cerr << "Error: Graph contains a negative-weight cycle.\n";
                return;
            }
        }
    }

    ofstream out(outputPath);
    for (auto [node, d] : dist) {
        out << src << " -> " << node << ": ";
        out << (d == INF ? "unreachable" : to_string(d)) << "\n";
    }

    trace.close();
    out.close();
    cout << "Bellman-Ford trace written to " << tracePath << "\n";
}


int main() {
    int source = 1;

    if (!loadGraph("../Dataset/bitcoin_weighted_edges.txt", true)) return 1;

    auto start = chrono::high_resolution_clock::now();
    bellmanFord(source, "../Results/bellmanford_result.txt", "../Results/bellmanford_trace.txt");
    auto end = chrono::high_resolution_clock::now();

    cout << "Bellman-Ford Time: " 
         << chrono::duration<double>(end - start).count() << "s\n";

    return 0;
}
