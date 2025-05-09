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

// Prim's Algorithm for MST
void primMST(int start) {
    unordered_map<int, bool> inMST;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    unordered_map<int, int> key, parent;

    for (int node : nodes) key[node] = numeric_limits<int>::max();
    key[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        inMST[u] = true;

        for (auto [v, w] : adj[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w, v});
                parent[v] = u;
            }
        }
    }

    ofstream out("../Results/prim_mst.txt");
    int totalWeight = 0;
    for (auto [v, u] : parent) {
        out << u << " - " << v << "\n";
        totalWeight += key[v];
    }
    out << "Total Weight: " << totalWeight << endl;
}


int main() {
    loadGraph("../Dataset/bitcoin_weighted_edges.txt", false); // Undirected for MST and cycle

    auto start = chrono::high_resolution_clock::now();
    primMST(*nodes.begin());
    auto end = chrono::high_resolution_clock::now();
    cout << "Prim's MST Time: " << chrono::duration<double>(end - start).count() << "s\n";

    return 0;
}
