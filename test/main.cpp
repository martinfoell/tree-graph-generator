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
    Tikz tikz;
    Layout layout;


    int V = 10; // Number of vertices in the graph
    int V_central = 3; // Number of vertices in the central path/tree
    int V_outer = V - V_central; // Number of vertices on the outer tree
    
    tikz.deleteBody();        
    tikz.premable();
    tikz.loop();
    tikz.tikzset();
    tikz.centralPath("central_tree", V_central, 0, 1, 0);
    
    Tree tree(V);
    Tree treeCentral(V); // Create a tree with 5 vertices    
    
    // initalize the central path
    treeCentral.centralPath(V_central);
    
    std::vector<int> leaves_central = treeCentral.leavesCentral(V_central);
    int L_central = leaves_central.size();

    int L = 6; // Number of leaves in the graph

    tree = treeCentral;    
    
    tikz.createDirectory(V, L);    
    tikz.deleteTrees(V, L);
    
    IntVector3D leaf_paths = leafPaths(L, L_central, V_outer, 1);
    std::cout << "leaf_paths: "<< std::endl;
    displayVec3(leaf_paths);

    std::cout << L_central << std::endl;
    std::cout << "leaves: ";
    printVector(leaves_central);
    
    // number of digits in tree index
    int digits = 5;
    // number of trees in a row
    int width = 3;

    
    // loop over all different configurations of the leaf paths
    for (int k = 0; k < leaf_paths.size(); k++){
      // use instead of empty_vertex if tikz only
      int last_vertex = V_central;
      // loop over all the leaves for one configuration
      for (int i = 0; i < leaf_paths[k].size(); i++) {
	IntVector leaf_path = leaf_paths[k][i];
	int leaf = leaves_central[i];
	// loop over each path for one leaf
	for (int j = 0; j < leaf_path.size(); j++) {
	  // std::cout << "length of leaf path: " << leaf_path.size() << std::endl;
	  std::vector<double> angles = layout.half(-180, -90, leaf_path.size(), -1+2*i);	  
	  // the first empty node in the tree
	  int empty_vertex = tree.emptyVertex();
	  // add the path to the tree
	  tree.addPath(leaf, empty_vertex, leaf_path[j]);
	  tikz.appendPath(V, L, leaf, last_vertex,  leaf_path[j], digits, k,  angles[j]);
	  last_vertex += leaf_path[j];
	}
      }
      
      tree.clear();
      tree = treeCentral;
    }
    
    tikz.makeTrees(V, L, width, digits, leaf_paths.size());    
    tikz.appendBody(V, L);
    tikz.writeMain();
    
    return 0;
}

