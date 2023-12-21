#include <iostream>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"
#include "../include/utils.hpp"

int main() {
    int V = 6; // Number of vertices in the graph

    int p = 1;
    int paths = 4;
    int c = 4;
    Tree treeCore(V); // Create a tree with 5 vertices
    Tree tree(V);
    treeCore.corePath(c);

    tree = treeCore;

    std::vector<int> leaves = tree.leaves();
    int nleaves = leaves.size();
    std::cout << nleaves << std::endl;
    std::cout << "leaves: ";
    printVector(leaves);
    

 

    // Display the adjacency list and the degree of each vertex
    tree.printGraph();
    tree.PrintDegree();
    tree.PrintLeaves();    
    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    std::vector<int> core = createVector(0, c-1);
    
    tikzloop();
    tikzset();
    tikzPath("core", core, 0, 1, 0);
    return 0;
}

    // erase and use treeCore again
    // tree.clear();
    // tree = treeCore;
    
    
    // tree.addPaths({0}, {path});
    // Add edges
    // Tree tree(V);
    // tree.addPaths({0,0,0}, {4,3,2});
    // tree.clear();
    // tree.addEdge(0, 1);
    // tree.addPath(1, 2, 3);
    // tree.addNodeInbetween(0, 1, 2);

