#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm> // For std::reverse
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Function to find the MST using Prim's algorithm
vector<Edge> findMSTPrim(const vector<vector<int> >& adjMatrix, int n) {
    vector<Edge> mst;
    vector<bool> inMST(n, false); // To track nodes included in MST
    vector<int> key(n, numeric_limits<int>::max()); // Weights to pick minimum weight edge
    vector<int> parent(n, -1); // Array to store constructed MST

    key[0] = 0; // Start from the first vertex

    for (int count = 0; count < n - 1; count++) {
        // Find the minimum key vertex not yet included in MST
        int minKey = numeric_limits<int>::max(), u = -1;
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true; // Add the selected vertex to the MST

        // Update key and parent for adjacent vertices of the selected vertex
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                key[v] = adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Store the MST edges
    for (int v = 1; v < n; v++) {
        if (parent[v] != -1) {
            mst.push_back(Edge(parent[v], v, adjMatrix[parent[v]][v]));
        }
    }

    return mst;
}

// DFS to find path from u to v in MST
bool dfsFindPath(int u, int v, const vector<vector<int> >& adjMST, vector<int>& path, vector<bool>& visited) {
    visited[u] = true;
    path.push_back(u);

    if (u == v) return true;

    for (const int neighbor : adjMST[u]) {
        if (!visited[neighbor] && dfsFindPath(neighbor, v, adjMST, path, visited)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

// Find fundamental circuits and cutsets
void findFundamentalCircuitsAndCutsets(const vector<Edge>& mst, const vector<Edge>& allEdges, int n) {
    // Create adjacency list for MST
    vector<vector<int> > adjMST(n);
    for (const auto& edge : mst) {
        adjMST[edge.u].push_back(edge.v);
        adjMST[edge.v].push_back(edge.u);
    }

    cout << "\nFundamental Circuits:\n";
    for (const auto& edge : allEdges) {
        // Check if edge is already in MST
        bool inMST = false;
        for (const auto& mstEdge : mst) {
            if ((mstEdge.u == edge.u && mstEdge.v == edge.v) || 
                (mstEdge.u == edge.v && mstEdge.v == edge.u)) {
                inMST = true;
                break;
            }
        }

        if (!inMST) {
            vector<int> path;
            vector<bool> visited(n, false);
            
            if (dfsFindPath(edge.u, edge.v, adjMST, path, visited)) {
                cout << "Circuit formed by adding edge (" << edge.u << ", " << edge.v << "): ";
                path.push_back(edge.u); // Close the circuit
                for (int i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        }
    }

    cout << "\nFundamental Cutsets:\n";
    for (const auto& edge : mst) {
        cout << "Removing edge (" << edge.u << ", " << edge.v << ") defines a cutset separating the graph.\n";
    }
}

int main() {
    int n; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int> > adjMatrix(n, vector<int>(n, 0));
    vector<Edge> allEdges;

    // Input the weighted adjacency matrix
    cout << "Enter the weighted adjacency matrix (enter 0 for no edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adjMatrix[i][j];
            if (i < j && adjMatrix[i][j] > 0) {
                allEdges.push_back(Edge(i, j, adjMatrix[i][j]));
            }
        }
    }

    // Find MST using Prim's algorithm
    vector<Edge> mst = findMSTPrim(adjMatrix, n);
    cout << "\nMinimum Spanning Tree edges:\n";
    for (auto& edge : mst) {
        cout << "(" << edge.u << ", " << edge.v << "), weight: " << edge.weight << "\n";
    }

    // Find all fundamental circuits and cutsets
    findFundamentalCircuitsAndCutsets(mst, allEdges, n);

    return 0;
}