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
    
    int V = 13; // Number of vertices in the graph
    int L = 4; // Number of leaves in the graph
    int V_central = 2; // Number of vertices in the central path/tree
    Tree tree(V); // create main tree

    int L_min;
    if ( V_central == 0 ) {
      L_min = 3;
    } else {
      L_min = 4;
    }
    int L_max = V - V_central + 1;

    int n = 0;
    for (int i = L_min; i < L_max; i++) {
      int m = tree.generateTrees(tree, V, i, V_central, width, digits);
      n += m;
    }
    std::cout << "Number of trees: " << n << std::endl;

    
    
    tex.writeMain();
    
    return 0;
}



