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
    
    int main_path = 2;
    int n_paths = 5;
    int total_path_nodes = V - main_path;
    std::cout << "total_path_nodes: " << total_path_nodes << std::endl;
    
    Tree mainPath(V); // Create a tree with 5 vertices
    // initalize the main path
    mainPath.corePath(main_path);
    tree = mainPath;
    
    // delete the content of the body of the main.tex file
    tikz.deleteBody();
    
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
    
    // number of digits in tree index
    size_t digits = 5;
    // number of trees in a row
    int width = 6;
    std::string node_folder = "n"+std::to_string(V);
    std::string leaf_folder = node_folder + "/l"+std::to_string(n_paths);
    createDirectory(node_folder);
    createDirectory(leaf_folder);
    tikz.deleteFilesInFolder(V, n_paths);
    
    // loop over all different configurations of the leaf paths
    for (int k = 0; k < leaf_paths.size(); k++){
      int tree_index = 0;      
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
	  tikz.addPath(V, n_paths, leaf, last_node,  leaf_path[j], digits, k, path_index, angles[j]);
	  last_node += leaf_path[j];
	  path_index++;
	}
      }
      // tree.printGraph();
      tree.clear();
      tree = mainPath;
    }
    tikz.inputTrees(V, width, digits, leaf_paths.size(), n_paths);
    tikz.appendBody(V, n_paths);
    
    tikz.writeMain();
    // tree.printGraph();
    // tree.PrintDegree();
    // tree.PrintLeaves();        
    // deleteFilesInFolder("");    

    std::vector<double> angles = layout.angle(-180,3);
    std::vector<double> left = layout.half(90,2, 1);
    std::vector<double> right = layout.half(90,2, -1);
    printVectord(angles);
    printVectord(left);
    printVectord(right);

    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    std::vector<int> core = createVector(0, main_path-1);
    
    tikz.premable();
    tikz.loop();
    tikz.tikzset();
    tikz.path("core", core, 0, 1, 0);
    return 0;
}

