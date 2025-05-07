// C++ implementations for CS-2009 project based on soc-sign-bitcoinotc dataset
// Algorithms: Diameter

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



int main() {
    loadGraph("bitcoin_weighted_edges.txt", true);
    int source = 1; // Choose appropriate source node



    return 0;
}
