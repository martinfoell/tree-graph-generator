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
    
    int main_path = 2;
    int n_paths = 4;
    int total_path_nodes = V - main_path;
    std::cout << "total_path_nodes: " << total_path_nodes << std::endl;
    
    Tree mainPath(V); // Create a tree with 5 vertices
    // initalize the main path
    mainPath.corePath(main_path);
    tree = mainPath;

    // tree.printGraph();

    std::vector<std::vector<int>> pp = partition(5, 2);
    print2DVector(pp);
    // Copy the core tree to the main tree
    // tree = mainPath;
    std::vector<int> leaves = tree.leaves();
    
    int n_leaves = leaves.size();
    std::cout << n_leaves << std::endl;
    std::cout << "leaves: ";
    printVector(leaves);
 
    IntVector3D leaf_paths = leafPaths(n_paths, n_leaves, total_path_nodes, 1);
    std::cout << "leaf_paths: "<< std::endl;
    displayVec3(leaf_paths);


    int index = 1;
    
    for (int k = 0; k < leaf_paths.size(); k++){
      int last_node = main_path;
      int tikz_index = 1;
      for (int i = 0; i < leaf_paths[k].size(); i++) {
	IntVector leaf_path = leaf_paths[k][i];
	printVector(leaf_path);
	std::vector<int> leaf(leaf_paths.size(), leaves[i]);
	tree.addPaths(leaf, leaf_path);
	std::vector<double> angles = layout.half(-90,2, -1+2*i);
	for (int j = 0; j < leaf_path.size(); j++) {
	  int start_node = leaves[i];
	  IntVector vec = createVector(last_node, last_node + leaf_path[j] - 1);
	  int angle = angles[j];
	  std::string name = "path_"+ std::to_string(k+1) + "_" + std::to_string(tikz_index);
	  tikzAddPath(name, start_node, vec, angle);
	  
	  // printing
	  std::cout << "start_node: " << start_node << std::endl;
	  std::cout << "vec: ";
	  printVector(vec);
	  std::cout << "angle: " << angle << std::endl;	
	  last_node += leaf_path[j];
	  tikz_index++;
	}
      }
      tree.printGraph();
      tree.clear();
      tree = mainPath;
    }
    

    
    
    tree.printGraph();
    tree.PrintDegree();
    

    std::vector<double> angles = layout.angle(-180,3);
    std::vector<double> left = layout.half(90,2, 1);
    std::vector<double> right = layout.half(90,2, -1);
    printVectord(angles);
    printVectord(left);
    printVectord(right);

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

