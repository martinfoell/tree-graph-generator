#include <iostream>
#include <utility>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"
#include "../include/utils.hpp"
#include "../include/layout.hpp"
#include <algorithm>
#include <iostream>
#include <string_view>

int main() {
    Layout layout;
    int V = 12; // Number of vertices in the graph
    Tree tree(V);
    Tikz tikz;
    
    int main_path = 3;
    int n_paths = 6;
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
    
    size_t n_zero = 3;

    std::string node_folder = "n"+std::to_string(V);
    createDirectory(node_folder);
    std::string leaf_folder = node_folder + "/l"+std::to_string(n_paths);
    createDirectory(leaf_folder);
    deleteFilesInFolder("");
    
    // loop over all different configurations of the leaf paths
    for (int k = 0; k < leaf_paths.size(); k++){
      int path_index = 1;
      // use instead of empty_vertex if tikz only
      int last_node = main_path;
      // loop over all the leaves for one configuration
      for (int i = 0; i < leaf_paths[k].size(); i++) {
	IntVector leaf_path = leaf_paths[k][i];
	int leaf = leaves[i];
	// loop over each path for one leaf
	for (int j = 0; j < leaf_path.size(); j++) {
	  // std::cout << "length of leaf path: " << leaf_path.size() << std::endl;
	  std::vector<double> angles = layout.half(-90, leaf_path.size(), -1+2*i);	  
	  // the first empty node in the tree
	  int empty_vertex = tree.emptyVertex();
	  // add the path to the tree
	  tree.addPath(leaf, empty_vertex, leaf_path[j]);
	  // add the path to the tikz layout
	  IntVector vec = createVector(last_node, last_node + leaf_path[j] - 1);
	  std::string k_old = std::to_string(k+1);
	  std::string k_new = std::string(n_zero - std::min(n_zero, k_old.length()), '0') + k_old;
	  std::string name = "path_"+ k_new + "_" + std::to_string(path_index);
	  tikz.addPath(name, leaf, vec, angles[j]);
	  last_node += leaf_path[j];
	  path_index++;
	}
      }
      // tree.printGraph();
      tree.clear();
      tree = mainPath;
    }
    

    
    
    tree.printGraph();
    tree.PrintDegree();
    // deleteFilesInFolder("");    

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
    
    tikz.premable();
    tikz.loop();
    tikz.tikzset();
    tikz.path("core", core, 0, 1, 0);
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

	  // // printing
	  // std::cout << "start_node: " << start_node << std::endl;
	  // std::cout << "vec: ";
	  // printVector(vec);
	  // std::cout << "angle: " << angle << std::endl;	

	// printVector(leaf_path);
	// std::vector<int> leaf(leaf_paths.size(), leaves[i]);
	// tree.addPaths(leaf, leaf_path);

