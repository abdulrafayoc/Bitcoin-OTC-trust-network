// C++ implementations for CS-2009 project
// Algorithms: Prim's MST, Kruskal's MST, Diameter of Graph, Cycle Detection, Average Degree

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


// Diameter of Graph using BFS
int bfsFurthest(int start, int &furthest) {
    unordered_map<int, int> dist;
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, w] : adj[u]) {
            if (dist.find(v) == dist.end()) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int maxDist = 0;
    for (auto [node, d] : dist) {
        if (d > maxDist) {
            maxDist = d;
            furthest = node;
        }
    }
    return maxDist;
}

void diameterOfGraph() {
    int node = *nodes.begin();
    int furthest;
    bfsFurthest(node, furthest);
    int diameter = bfsFurthest(furthest, node);

    ofstream out("../Results/diameter.txt");
    out << "Diameter of graph: " << diameter << endl;
}



int main() {
    loadGraph("../Dataset/bitcoin_weighted_edges.txt", false);
    

    diameterOfGraph();

    return 0;
}
