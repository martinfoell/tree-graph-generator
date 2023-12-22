#include <iostream>
#include <utility>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"
#include "../include/utils.hpp"
#include "../include/layout.hpp"

int main() {
    Layout layout;
    int V = 8; // Number of vertices in the graph
    Tree tree(V);
    
    int p = 1;
    int main_path = 2;
    int total_path_nodes = 6;
    std::cout << "total_path_nodes: " << total_path_nodes << std::endl;
    if (main_path > 1){
      Tree mainPath(V); // Create a tree with 5 vertices
      // initalize the main path
      mainPath.corePath(main_path);
      tree = mainPath;
    }
    tree.printGraph();


    // Copy the core tree to the main tree
    // tree = mainPath;
    std::vector<int> leaves = tree.leaves();
    int n_paths = 4;
    int n_leaves = leaves.size();
    std::cout << n_leaves << std::endl;
    std::cout << "leaves: ";
    printVector(leaves);

 
    IntVector3D leaf_paths = leafPaths(n_paths, n_leaves, total_path_nodes, 1);

    
    
    std::cout << "leaf_paths: "<< std::endl;
    displayVec3(leaf_paths);


    
    std::vector<int> leaves_dist = {2,2};
    
    std::vector<int> partition2 = {1,1,2,2};

    
    // std::vector<std::vector<int>> partition_perm = permutations(partition2);
    // std::vector<int> leaves_split = cumulative(leaves_dist);
    
    
    std::vector<int> part = {1,1};
    std::vector<std::vector<int>> par = {{1,2},{1,2}};
    std::vector<std::pair<int, int> > vec1 = { {1, 0}, {2,0}, {3,1} };

    for (int i = 0; i < leaves.size(); i++) {
      int leaf = leaves[i];
      std::vector<int> vec = par[i];
      tree.addPaths({leaf,leaf}, vec);
    }
    tree.printGraph();
    tree.PrintDegree();
    

    std::vector<double> angles = layout.angle(-180,3);
    std::vector<double> left = layout.left(90,2);
    printVectord(angles);
    printVectord(left);

    // Display the adjacency list and the degree of each vertex
    // tree.printGraph();
    // tree.PrintDegree();
    // tree.PrintLeaves();    
    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    std::vector<int> core = createVector(0, main_path-1);
    
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

