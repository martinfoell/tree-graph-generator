#include "../include/tree.hpp"


// Constructor definition
Tree::Tree(int vertices) {
    V = vertices;
    adjList.resize(V);
}

// Function to add an edge between vertex u and vertex v
void Tree::addEdge(int u, int v) {
    // For an undirected graph, add edges in both directions
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

// Function to display the adjacency list representation of the graph
void Tree::printGraph() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Adjacency list of vertex " << i << ":\n";
        std::cout << "head";
        for (int j = 0; j < adjList[i].size(); ++j) {
            std::cout << " -> " << adjList[i][j];
        }
        std::cout << std::endl;
    }
}


