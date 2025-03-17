#include "dijkstras.h"

using namespace std;

int main() {
    Graph G;
    // file_to_graph("src/small.txt", G);
    // file_to_graph("src/medium.txt", G);
    // file_to_graph("src/large.txt", G);
    file_to_graph("src/largest.txt", G);

    vector<int> prev;
    vector<int> dist = dijkstra_shortest_path(G, 0, prev);

    cout << "$ dijkstras small.txt"<< endl;
    
    for (int dest = 0; dest < G.numVertices; dest++) {
        vector<int> path = extract_shortest_path(dist, prev, dest);
        print_path(path, dist[dest]);
    }

    return 0;
}