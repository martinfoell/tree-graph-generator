#include <iostream>
#include <utility>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"
#include "../include/tex.hpp"
#include "../include/utils.hpp"
#include "../include/layout.hpp"
#include <algorithm>
#include <iostream>
#include <string_view>

int main() {


    Tikz tikzinit(0,0,0);
    Tex tex;
    
    tex.deleteBody();        
    tex.premable();
    tex.tikzloop();
    tex.tikzset();

    
    // number of digits in tree index
    int digits = 5;
    // number of trees in a row
    int width = 4;
    
    // idea: need to prune the tree to remove vertices that have degree 1 and 2
    // perbutative tree generation
    
    int V = 9; // Number of vertices in the graph
    for (int V = 8; V < 12; V++) {
      Tree tree(V); // create main tree      
      // int V_central = 3; // Number of vertices in the central path/tree

      int V_central_min = 1; // Number of vertices in the central path/tree
      int V_central_max = std::max(1, V - 4); // Number of vertices in the central path/tree    
      IntVector3D decomp;
      IntVector decompSum;
      decomp.resize(V_central_max - V_central_min + 1);
      decompSum.resize(V_central_max - V_central_min + 1);      
    
      int n = 0;
      for (int V_central = V_central_min; V_central <= V_central_max; V_central++) {

	int v = 0;
	int L_min;    
	if (V_central <= 1) {
	  L_min = 3;  // allow small central paths or no central path
	} else {
	  L_min = 4;
	}    

	IntVector2D L_vector;
      
	int L_max = V - V_central + 1;
	for (int i = L_min; i < L_max; i++) {
	  int m = tree.generateTrees2(V, i, V_central, width, digits);
	  // int m = tree.generateTrees(tree, V, i, V_central, width, digits);
	  n += m;
	  v += m;
	  L_vector.push_back({m});      
	}
	// Reverse L_vector before appending
	std::reverse(L_vector.begin(), L_vector.end());
      
	decomp[V_central - V_central_min] = L_vector;
	decompSum[V_central - V_central_min] = v;	
      }
      std::reverse(decomp.begin(), decomp.end());
      std::reverse(decompSum.begin(), decompSum.end());      
      // printVector3D(decomp);
      printVector(decompSum);      
      std::cout << "Number of trees: " << n << std::endl;
      tex.writeMain();
    }
    return 0;


}



