#include "./dijkstras.h"

int main(int argc, char *argv[]) {
    string file_name = (argc > 1) ? argv[1] : "../src/small.txt";
    Graph G;
    file_to_graph(file_name, G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    cout << "dijkstras " << file_name << endl;
    for (int dst = 0; dst < G.numVertices; ++dst) {
        vector<int> shortestPath = extract_shortest_path(distances, previous, dst);
        print_path(shortestPath, distances[dst]);
    }
}