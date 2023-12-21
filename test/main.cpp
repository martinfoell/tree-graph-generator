#include <iostream>
#include "../include/tree.hpp"



int main() {
    int V = 5; // Number of vertices in the graph
    Tree graph(V); // Create a graph with 5 vertices

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Display the adjacency list
    graph.printGraph();

    return 0;
}

// int main(){
//   Graph graph(10);
//   graph.addEdge(0, 1);
//   graph.addEdge(0, 3);
//   graph.addEdge(0, 4);    
//   graph.printGraph();

//   return 0;  
// }
