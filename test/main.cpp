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

    int L = 10; // Number of leaves in the graph
    int C_L = 5; // Number of leaves in the central path/tree

    IntVector2D part = partition(L, C_L);
    std::cout << "Partition: " << std::endl;
    printVector2D(part);

    IntVector3D all_permutations;
    for (int i = 0; i < part.size(); i++) {
      IntVector2D perm = permutations(part[i]);
      all_permutations.push_back(perm);
    }

    printVector3D(all_permutations);
    IntVector2D all_permutations_2d = flattenVec3ToVec2(all_permutations);
    std::cout << "Permutations: " << std::endl;
    // printVector2D(all_permutations_2d);
    std::cout << "Number of permutations: " << all_permutations_2d.size() << std::endl;

    std::vector<double> test = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    printVector(test);

    
    return 0;


}



