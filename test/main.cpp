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
    
    tikz.deleteBody();        
    tikz.premable();
    tikz.loop();
    tikz.tikzset();
    
    // number of digits in tree index
    int digits = 5;
    // number of trees in a row
    int width = 3;
    
    // idea: need to prune the tree to remove vertices that have degree 1 and 2
    // perbutative tree generation
    
    int V = 9; // Number of vertices in the graph
    int L = 4; // Number of leaves in the graph
    int V_central = 2; // Number of vertices in the central path/tree
    
    tikz.centralPath("central_tree", V_central, 0);
    Tree tree(V); // create main tree
    Tree treeCentral(V); // create central tree
    
    // initalize the central path
    treeCentral.centralPath(V_central);
    tree = treeCentral;        
    std::vector<int> leaves_central = treeCentral.leavesCentral(V_central);
    int L_central = leaves_central.size();
    std::cout << "L_central: " << L_central << std::endl;
    
    tikz.createDirectory(V, L);    
    tikz.deleteTrees(V, L);
    
    IntVector3D paths = findAllPaths(V, L, V_central, L_central, 1);
    
    // loop over all different configurations of the leaf paths
    for (int k = 0; k < paths.size(); k++){
      // use instead of empty_vertex if tikz only
      int last_vertex = V_central;
      // loop over all the leaves for one configuration
      for (int i = 0; i < paths[k].size(); i++) {
	IntVector path = paths[k][i];
	int leaf_central = leaves_central[i];
	// loop over each path for one leaf
	for (int j = 0; j < path.size(); j++) {
	  std::cout << "path: " << path.size() << std::endl;
	  std::vector<double> angles = layout.half(-180, -90, V_central, path.size(), -1+2*i);	  
	  // the first empty node in the tree
	  int empty_vertex = tree.emptyVertex();
	  // add the path to the tree
	  tree.addPath(leaf_central, empty_vertex, path[j]);
	  tikz.appendPath(V, L, leaf_central, last_vertex,  path[j], digits, k,  angles[j]);
	  last_vertex += path[j];
	}
      }

      tree.clear();
      tree = treeCentral;
    }
    // if (Print) {
      std::cout << "paths: "<< std::endl;
      displayVec3(paths);
    // }
    tikz.makeTrees(V, L, width, digits, paths.size());    
    tikz.appendBody(V, L);

    
    tikz.writeMain();
    
    return 0;
}



