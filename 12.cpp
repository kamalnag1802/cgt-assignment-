#include <iostream>
#include <vector>

using namespace std;

// Function to check if the graph has an Euler path or circuit
void findEulerPath(int currentVertex, vector<vector<int> >& adjMatrix, vector<int>& path) {
    for (int nextVertex = 0; nextVertex < adjMatrix.size(); nextVertex++) {
        // If there is an edge between currentVertex and nextVertex
        if (adjMatrix[currentVertex][nextVertex] == 1) {
            // Remove the edge
            adjMatrix[currentVertex][nextVertex] = 0;
            adjMatrix[nextVertex][currentVertex] = 0;

            // Recursively find the next part of the Euler path/circuit
            findEulerPath(nextVertex, adjMatrix, path);
        }
    }
    // Add the vertex to the path after all edges are traversed
    path.push_back(currentVertex);
}

void eulerPath(vector<vector<int> >& adjMatrix) {
    int numVertices = adjMatrix.size();
    int oddDegreeVertices = 0;
    vector<int> startVertices;

    // Count the number of vertices with odd degrees
    for (int i = 0; i < numVertices; i++) {
        int degree = 0;
        for (int j = 0; j < numVertices; j++) {
            degree += adjMatrix[i][j];
        }
        if (degree % 2 != 0) {
            oddDegreeVertices++;
            startVertices.push_back(i);
        }
    }

    // Check if the graph has an Euler path or circuit
    if (oddDegreeVertices > 2) {
        cout << "No Euler path or circuit exists." << endl;
    } else {
        vector<int> path;
        int startVertex;

        if (oddDegreeVertices == 2) {
            // Euler path exists
            cout << "Euler path exists." << endl;
            startVertex = startVertices[0];  // Start from any odd degree vertex
        } else {
            // Euler circuit exists
            cout << "Euler circuit exists." << endl;
            startVertex = 0;  // Start from any vertex if all have even degrees
        }

        // Use recursive function to find the Euler path/circuit
        findEulerPath(startVertex, adjMatrix, path);

        // Reverse the path and print it
        reverse(path.begin(), path.end());
        cout << "Euler Path/Circuit: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    if (numVertices <= 0) {
        cout << "Invalid number of vertices." << endl;
        return 1;
    }

    // Create an adjacency matrix
    vector<vector<int> > adjMatrix(numVertices, vector<int>(numVertices, 0));
    cout << "Enter the adjacency matrix (0 or 1 values only):" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cin >> adjMatrix[i][j];
            if (adjMatrix[i][j] < 0 || adjMatrix[i][j] > 1) {
                cout << "Invalid input. Please enter 0 or 1." << endl;
                return 1;
            }
        }
    }

    // Call the function to
      eulerPath(adjMatrix);

    return 0;
}