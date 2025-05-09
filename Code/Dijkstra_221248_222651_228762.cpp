// C++ implementations for CS-2009 project based on soc-sign-bitcoinotc dataset
// Algorithms: Dijkstra

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

// Dijkstra's algorithm for single source shortest path
void dijkstra(int source) {
    ofstream traceFile("../Results/dijkstra_trace.txt");
    ofstream resultFile("../Results/dijkstra_shortest_paths.txt");
    
    // Initialize distances
    unordered_map<int, int> dist;
    unordered_map<int, int> prev;
    
    for (int node : nodes) {
        dist[node] = numeric_limits<int>::max();
        prev[node] = -1;
    }
    dist[source] = 0;
    
    // Priority queue for efficient implementation
    // We use pair of (distance, node) for the priority queue
    // Using a min-heap (ordered by distance)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    traceFile << "Dijkstra's Algorithm Trace:\n";
    traceFile << "------------------------\n";
    traceFile << "Initial state: Source node " << source << " with distance 0\n";
    traceFile << "Priority Queue (distance, node): (0, " << source << ")\n\n";
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        
        traceFile << "Removed from queue: node " << u << " with distance " << dist_u << "\n";
        
        // Skip if we've already found a better path
        if (dist_u > dist[u]) continue;
        
        for (auto& [v, weight] : adj[u]) {
            int alt = dist[u] + weight;
            traceFile << "  Considering edge " << u << " -> " << v << " with weight " << weight << "\n";
            traceFile << "  Current distance to " << v << ": " << (dist[v] == numeric_limits<int>::max() ? "INF" : to_string(dist[v])) << "\n";
            traceFile << "  New potential distance: " << alt << "\n";
            
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
                traceFile << "  Updated distance to " << v << ": " << alt << "\n";
                traceFile << "  Added to queue: (" << alt << ", " << v << ")\n";
            } else {
                traceFile << "  No update needed\n";
            }
        }
        
        traceFile << "Current queue: ";
        if (pq.empty()) {
            traceFile << "empty";
        } else {
            // We can't directly iterate over a priority queue, so we'll just note the size
            traceFile << "contains " << pq.size() << " elements";
        }
        traceFile << "\n\n";
    }
    
    // Store shortest paths in file
    resultFile << "Shortest paths from source node " << source << ":\n";
    resultFile << "-----------------------------------\n";
    for (int node : nodes) {
        if (node == source) continue;
        
        resultFile << "Path to node " << node << ": ";
        if (dist[node] == numeric_limits<int>::max()) {
            resultFile << "No path exists\n";
            continue;
        }
        
        resultFile << "Distance = " << dist[node] << ", Path: ";
        
        // Reconstruct path
        vector<int> path;
        for (int at = node; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); i++) {
            resultFile << path[i];
            if (i < path.size() - 1) resultFile << " -> ";
        }
        resultFile << "\n";
    }
    
    // Also display on console
    cout << "Dijkstra's algorithm completed. Results saved to 'dijkstra_shortest_paths.txt'\n";
    cout << "Trace saved to 'dijkstra_trace.txt'\n";
}

int main() {
    // Load the graph
    loadGraph("../Dataset/bitcoin_weighted_edges.txt");
    
    // Measure execution time
    auto start = chrono::high_resolution_clock::now();
    
    // Choose a source node (for example, the first node in the set)
    int source = *nodes.begin();
    dijkstra(source);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    // Store execution time
    ofstream timeFile("../Results/dijkstra_execution_time.txt");
    timeFile << "Dijkstra's Algorithm Execution Time: " << duration << " milliseconds" << endl;
    
    cout << "Execution time: " << duration << " milliseconds" << endl;
    
    return 0;
}