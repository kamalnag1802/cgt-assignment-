#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm> // For std::reverse

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int destination;
    int weight;

    // Constructor for Edge
    Edge(int d, int w) : destination(d), weight(w) {}
};

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(const vector<vector<Edge> >& graph, int source) {
    int numVertices = graph.size();
    vector<int> distance(numVertices, INF);
    vector<int> parent(numVertices, -1); // To recover paths
    vector<bool> visited(numVertices, false);
    
    // Min-priority queue: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    distance[source] = 0;
    pq.push(make_pair(0, source)); // Push the source with distance 0

    while (!pq.empty()) {
        int u = pq.top().second;  // Get the vertex with the smallest distance
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        // Traverse adjacent edges
        for (const auto& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // Relaxation step
            if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;  // Update parent to track the path
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    // Print distances from source
    cout << "Shortest distances from source vertex " << source << ":\n";
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": " << distance[i];
        if (distance[i] == INF) {
            cout << " (Unreachable)";
        }
        cout << endl;
    }

    // Print paths from source
    cout << "\nPaths from source vertex " << source << ":\n";
    for (int i = 0; i < numVertices; i++) {
        if (distance[i] == INF) {
            cout << "Vertex " << i << ": No path (Disconnected)\n";
        } else {
            cout << "Vertex " << i << ": ";
            vector<int> path;
            for (int v = i; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
            for (size_t j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j != path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
    }
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<Edge> > graph(numVertices);

    cout << "Enter the edges (format: u v w), where u and v are vertices (0-indexed) and w is the weight:\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(Edge(v, w));  // Directed edge u -> v with weight w
        graph[v].push_back(Edge(u, w));  // Undirected edge v -> u with weight w
    }

    int sourceVertex;
    cout << "Enter the source vertex: ";
    cin >> sourceVertex;

    dijkstra(graph, sourceVertex);

    return 0;
}