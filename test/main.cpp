#include <iostream>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"


int main() {
    int V =13; // Number of vertices in the graph
    Tree tree(V); // Create a tree with 5 vertices

    // Add edges
    tree.addPaths({0,0,0}, {4,3,2});
    
    // tree.addEdge(0, 1);
    // tree.addPath(1, 2, 3);
    // tree.addNodeInbetween(0, 1, 2);

 


    // Display the adjacency list and the degree of each vertex
    tree.printGraph();
    tree.PrintDegree();
    tree.PrintLeaves();    
    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    tikzloop();
    tikzset();
    std::vector<int> vec = {0,1,2,3,4,5};
    tikzinital(vec, 45, 1, 0);
    return 0;
}
