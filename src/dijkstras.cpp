#include "./dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    size_t n = G.numVertices;
    vector<int> vertexDistances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pqDatatype, vector<pqDatatype>, MinHeapCompare> pq;
    pq.push({source, 0});
    vertexDistances[source] = 0;
    while (!pq.empty()) {
        pqDatatype current = pq.top();
        pq.pop();
        int u = current.first;
        int distance = current.second;
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distance + weight < vertexDistances[v]) {
                vertexDistances[v] = distance + weight;
                previous[v] = u;
                pq.push({v, vertexDistances[v]});
            }
        }
    }
    return vertexDistances;
}

vector<int> extract_shortest_path(const vector<int>& previous, int destination) {
    stack<int> tempPath;
    vector<int> shortestPath;
    for (int current = destination; current != -1; current = previous[current])
        tempPath.push(current);
    while (!tempPath.empty()) {
        shortestPath.emplace_back(tempPath.top());
        tempPath.pop();
    }
    return shortestPath;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v)
        cout << vertex << ' ';
    cout << endl;
    cout << "Total cost is " << total << endl;
}

bool MinHeapCompare::operator()(const pqDatatype& v1, const pqDatatype& v2) {
    return v1.second > v2.second;
}