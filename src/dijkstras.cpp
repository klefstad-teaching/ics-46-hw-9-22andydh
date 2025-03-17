#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF); 
    vector<bool> visited(numVertices, false); 
    distances[source] = 0; // initialized to 0
    previous.assign(numVertices, -1); 

    // priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

    minHeap.push({0, source}); // adds the source node 

    // runs as long as not empty
    while (!minHeap.empty()) {
        // stores it in u
        int u = minHeap.top().second;
        minHeap.pop();

        // skips if already visited
        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // updates shortest path if shorter is found
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight; // updates distance
                previous[v] = u; 
                minHeap.push({distances[v], v}); // adds distance to pq
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());

    return path;
}

void print_path(const vector<int>& v, int total) {
    // check if empty
    if (v.empty()) {
        cout << "Path not found: " << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << " ";
        }
    }

    cout << " \nTotal cost is " << total << endl;
}
