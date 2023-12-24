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
    int V = 20; // Number of vertices in the graph
    Tree tree(V);
    Tikz tikz;
    
    int main_path = 2;
    Tree mainPath(V); // Create a tree with 5 vertices
    // initalize the main path
    mainPath.corePath(main_path);
    tree = mainPath;

    // find the leaves on the main path
    std::vector<int> leaves;
    if (main_path == 1){
      leaves = {0};
    }
    else if (main_path > 1){
      leaves = tree.leaves();      
    }
    int n_leaves = leaves.size();
    std::cout << "leaves: " << n_leaves << std::endl;
    int n_paths =6;
    int total_path_nodes = V - main_path;
    std::cout << "total_path_nodes: " << total_path_nodes << std::endl;
    
    
    // delete the content of the body of the main.tex file
    tikz.deleteBody();
    
    // tree.printGraph();

    // Copy the core tree to the main tree
    // tree = mainPath;
    // std::vector<int> leaves = tree.leaves();
 
    IntVector3D leaf_paths = leafPaths(n_paths, n_leaves, total_path_nodes, 1);
    std::cout << "leaf_paths: "<< std::endl;
    displayVec3(leaf_paths);

    std::cout << n_leaves << std::endl;
    std::cout << "leaves: ";
    printVector(leaves);
    
    // number of digits in tree index
    size_t digits = 5;
    // number of trees in a row
    int width = 3;
    std::string node_folder = "n"+std::to_string(V);
    std::string leaf_folder = node_folder + "/l"+std::to_string(n_paths);
    createDirectory(node_folder);
    createDirectory(leaf_folder);
    tikz.deleteFilesInFolder(V, n_paths);
    
    // loop over all different configurations of the leaf paths
    for (int k = 0; k < leaf_paths.size(); k++){
      // use instead of empty_vertex if tikz only
      int last_node = main_path;
      // loop over all the leaves for one configuration
      for (int i = 0; i < leaf_paths[k].size(); i++) {
	IntVector leaf_path = leaf_paths[k][i];
	int leaf = leaves[i];
	// loop over each path for one leaf
	for (int j = 0; j < leaf_path.size(); j++) {
	  // std::cout << "length of leaf path: " << leaf_path.size() << std::endl;
	  // std::vector<double> angles = layout.angle(-180, leaf_path.size());
	  std::vector<double> angles = layout.half(-180, -90, leaf_path.size(), -1+2*i);	  
	  // the first empty node in the tree
	  int empty_vertex = tree.emptyVertex();
	  // add the path to the tree
	  tree.addPath(leaf, empty_vertex, leaf_path[j]);
	  tikz.appendPath(V, n_paths, leaf, last_node,  leaf_path[j], digits, k,  angles[j]);
	  last_node += leaf_path[j];
	}
      }
      // tree.printGraph();
      tree.clear();
      tree = mainPath;
    }
    // tikz.inputTrees(V, width, digits, leaf_paths.size(), n_paths);
    tikz.makeTrees(V, width, digits, leaf_paths.size(), n_paths);    
    tikz.appendBody(V, n_paths);
    
    tikz.writeMain();
    
    // std::vector<double> angles1 = layout.angle(-180, 4);	  
    // printVectord(angles1);
    // tree.printGraph();
    // tree.PrintDegree();
    // tree.PrintLeaves();        
    // deleteFilesInFolder("");    

    // std::vector<double> angles = layout.angle(-180,3);
    // std::vector<double> left = layout.half(90,2, 1);
    // std::vector<double> right = layout.half(90,2, -1);
    // printVectord(angles);
    // printVectord(left);
    // printVectord(right);

    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    std::vector<int> core = createVector(0, main_path-1);
    
    tikz.premable();
    tikz.loop();
    tikz.tikzset();
    tikz.path("core", core, 0, 1, 0);
    return 0;
}

