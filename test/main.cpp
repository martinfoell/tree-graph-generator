#include <iostream>
#include <utility>
#include "../include/tree.hpp"
#include "../include/tikz.hpp"
#include "../include/utils.hpp"
#include "../include/layout.hpp"

int main() {
    Layout layout;
    int V = 12; // Number of vertices in the graph

    int p = 1;
    int c = 4;
    Tree treeCore(V); // Create a tree with 5 vertices
    Tree tree(V);
    treeCore.corePath(c);

    tree = treeCore;
    std::vector<int> leaves = tree.leaves();
    std::vector<int> part = {1,1};
    std::vector<std::vector<int>> par = {{1,2},{1,2}};
    std::vector<std::pair<int, int> > vec1 = { {1, 0}, {2,0}, {3,1} };

    for (int i = 0; i < leaves.size(); i++) {
      int leaf = leaves[i];
      std::vector<int> vec = par[i];
      tree.addPaths({leaf,leaf}, vec);
    }
    int nleaves = leaves.size();
    std::cout << nleaves << std::endl;
    std::cout << "leaves: ";
    printVector(leaves);
    
    std::vector<int> partition2 = {1,1,2,2};
    
    int paths = 6;
    std::vector<std::vector<int>> paths_config = filterVectors(partition(paths, nleaves),1);
    std::vector<int> leaves_dist = {2,2};
    print2DVector(paths_config);
    
    std::vector<std::vector<int>> partition_perm = permutations(partition2);
    std::vector<int> leaves_split = cumulative(leaves_dist);

    printVector(leaves_split);
    for (int i = 0; i < partition_perm.size(); i++ ){
      printVector(partition_perm[i]);      
    }

    IntVector3D leafPaths;
    IntVector2D leafPaths_perm;
    for (int i = 0; i < partition_perm.size(); i++ ){
      IntVector single_permutation = partition_perm[i];
      IntVector2D leafPaths_perm;	
      for (int j = 0; j < leaves_split.size()-1; j++ ){
	IntVector spl = slicing(single_permutation, leaves_split[j], leaves_split[j+1]-1);
	leafPaths_perm.push_back(spl);
      }
      leafPaths.push_back(leafPaths_perm);
    }

    displayVec3(leafPaths);
    sortVec3(leafPaths);
    std::cout<<"_________________"<<std::endl;
    displayVec3(leafPaths);

    std::vector<double> angles = layout.angle(-180,3);
    std::vector<double> left = layout.left(90,2);
    printVectord(angles);
    printVectord(left);

    // Display the adjacency list and the degree of each vertex
    // tree.printGraph();
    // tree.PrintDegree();
    // tree.PrintLeaves();    
    std::cout<<"Last vertex: "<<tree.emptyVertex()<<std::endl;    

    std::vector<int> core = createVector(0, c-1);
    
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

