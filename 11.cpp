#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair and std::make_pair

using namespace std;

bool graphExists(vector<int>& a, int n) {
    while (true) {
        // Sort the list in non-decreasing order
        sort(a.begin(), a.end(), greater<int>()); // Specify the type

        // Check if all the elements are equal to 0
        if (a[0] == 0) {
            return true;
        }

        // Store the first element in a variable and delete it from the list
        int v = a[0];
        a.erase(a.begin() + 0);

        // Check if enough elements are present in the list
        if (v > a.size()) {
            return false;
        }

        // Subtract first element from next v elements
        for (int i = 0; i < v; i++) {
            a[i]--;

            // Check if negative element is encountered after subtraction
            if (a[i] < 0) {
                return false;
            }
        }
    }
}

// Function to create an adjacency matrix from a given degree sequence
vector<vector<int> > createAdjacencyMatrix(vector<int> degrees) {
    int n = degrees.size();
    
    // Initialize the adjacency matrix with zeros
    vector<vector<int> > adjMatrix(n, vector<int>(n, 0));
    
    // Vector to store vertex indices along with their degrees
    vector<pair<int, int> > vertexDegrees;
    for (int i = 0; i < n; ++i) {
        vertexDegrees.push_back(make_pair(degrees[i], i)); // Use make_pair
    }
    
    // Iterate to connect vertices with remaining degrees
    while (true) {
        // Sort vertices by degree in descending order
        sort(vertexDegrees.rbegin(), vertexDegrees.rend());
        
        // If the largest degree is zero, we are done
        if (vertexDegrees[0].first == 0) {
            break;
        }
        
        // Get the vertex with the highest degree
        int d = vertexDegrees[0].first;
        int u = vertexDegrees[0].second;
        
        // Set the degree of the current vertex to zero (processed)
        vertexDegrees[0].first = 0;
        
        // Connect this vertex to the next 'd' vertices
        for (int i = 1; i <= d; ++i) {
            int v = vertexDegrees[i].second;
            
            // Create an edge between u and v
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            
            // Decrease the degree of the connected vertex
            vertexDegrees[i].first--;
        }
    }
    
    return adjMatrix;
}

// Function to display the adjacency matrix
void displayAdjMatrix(const vector<vector<int> >& adjMatrix) {
    for (const auto& row : adjMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int m;
    cout << "Enter the number of elements: ";
    cin >> m;

    vector<int> vec(m); // Create a vector with 'n' elements

    cout << "Enter the elements:\n";
    for (int i = 0; i < m; ++i) {
        cin >> vec[i]; // Take input for each element
    }

    vector<int> degrees1;
    vector<int> degrees2;
    degrees2.assign(vec.begin(), vec.end());
    degrees1.assign(vec.begin(), vec.end());

    if (graphExists(degrees2, m)) {
        cout << "Graph exists" << endl;
        vector<vector<int> > adjMatrix = createAdjacencyMatrix(degrees1);
        cout << "Adjacency Matrix:" << endl;
        displayAdjMatrix(adjMatrix);
    } else {
        cout << "Graph does not exist" << endl;
    }

    return 0;
}