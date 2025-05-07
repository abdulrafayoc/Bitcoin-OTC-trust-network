// C++ implementations for CS-2009 project based on soc-sign-bitcoinotc dataset
// Algorithms: Dijkstra

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

// Dijkstra's Algorithm (only works with non-negative weights)
void dijkstra(int src) {
    unordered_map<int, int> dist;
    for (int node : nodes) dist[node] = INF;
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for (Edge e : graph[u]) {
            if (e.weight < 0) continue;
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    ofstream out("dijkstra_result.txt");
    for (auto [node, d] : dist)
        out << src << " -> " << node << ": " << d << "\n";
}

int main() {
    loadGraph("bitcoin_weighted_edges.txt", true);
    int source = 1; // Choose appropriate source node

    auto start = chrono::high_resolution_clock::now();
    dijkstra(source);
    auto end = chrono::high_resolution_clock::now();
    cout << "Dijkstra Time: " << chrono::duration<double>(end - start).count() << "s\n";


    return 0;
}
