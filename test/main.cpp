#include <iostream>
#include "../include/tree.hpp"



int main() {
    int V =13; // Number of vertices in the graph
    Tree tree(V); // Create a tree with 5 vertices

    // Add edges
    tree.addPaths({0,0,0}, {4,3,2});
    // tree.addEdge(0, 1);
    // tree.addPath(1, 2, 3);
    // tree.addNodeInbetween(0, 1, 2);

    // tree.addEdge(0, 4);
    // tree.addEdge(1, 2);
    // tree.addEdge(1, 3);
    // tree.addEdge(1, 4);
    // tree.addEdge(2, 3);
    // tree.addEdge(3, 4);

    // Display the adjacency list
    tree.printGraph();
    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

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
