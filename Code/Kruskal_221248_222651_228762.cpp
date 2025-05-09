// C++ implementations for CS-2009 project
// Algorithms: Kruskal's MST 

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


// Disjoint Set for Kruskal
unordered_map<int, int> parent;
int find(int u) {
    if (parent[u] != u) parent[u] = find(parent[u]);
    return parent[u];
}
void unite(int u, int v) {
    parent[find(u)] = find(v);
}

// Kruskal's Algorithm for MST
void kruskalMST() {
    for (int node : nodes) parent[node] = node;
    sort(allEdges.begin(), allEdges.end());
    ofstream out("../Results/kruskal_mst.txt");
    int totalWeight = 0;
    for (Edge e : allEdges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            out << e.u << " - " << e.v << "\n";
            totalWeight += e.weight;
        }
    }
    out << "Total Weight: " << totalWeight << endl;
}


int main() {
    loadGraph("../Dataset/bitcoin_weighted_edges.txt", false); // Undirected for MST and cycle

    auto start = chrono::high_resolution_clock::now();
    kruskalMST();
    auto end = chrono::high_resolution_clock::now();
    cout << "Kruskal's MST Time: " << chrono::duration<double>(end - start).count() << "s\n";

    return 0;
}
