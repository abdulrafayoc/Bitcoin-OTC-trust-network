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


// Average Degree Calculation
void averageDegree(int source) {
    double totalDegree = 0;
    for (auto& [node, neighbors] : adj) {
        totalDegree += neighbors.size();
    }
    double avg = totalDegree / nodes.size();
    ofstream out("../Results/average_degree.txt");
    out << "Average Degree: " << avg << endl;
    cout << "Average Degree: " << avg << endl;
}

int main() {
    loadGraph("../Dataset/../Dataset/bitcoin_weighted_edges.txt", false); // Undirected for MST and cycle

    averageDegree(1);

    return 0;
}
