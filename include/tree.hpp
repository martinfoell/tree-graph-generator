#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <climits>
#include <numeric>
#include <functional>
#include <cassert>
#include <cctype>
#include <bitset>
#include <list>
#include <deque>
#include <utility>
#include <random>
#include <chrono>
#include <ctime>




class Tree {
private:
    int V; // Number of vertices
    std::vector<std::vector<int>> adjList; // Adjacency list

public:
  // Constructor to initialize the graph with V vertices
  Tree(int vertices);

  // Find the degree of a vertex
  int degree(int vertex);
  
  // Make a map of all vertices with degree above n, and save the degree of each vertex
  std::map<int,int> degree_n(int n);


  int shortestPath(int source, int destination);
  int diameter();
    
  // Function to find all leaves in the tree
  std::vector<int> leaves();

  std::vector<int> leavesCentral(int V_central);  
  // Function to find the first empty vertex in the adjacency list
  int emptyVertex();
  
  // Function to add an edge between vertex u and vertex v
  void addEdge(int u, int v);

  // Function to add a new vertex between vertex u and vertex v
  void addNodeInbetween(int u, int v, int v_new);

  // Function to add a path from a curent nude to the next and so on with length l
  void addPath(int curr, int next, int length);

  // Function to add the core path from vertex 0 to l-1
  void centralPath(int length);

  // Clear the edges of the tree
  void clear();

  int generateTrees(Tree tree, int V, int L, int V_central, int width, int digits);  
  //////// Print functions ////////
  
  // Function to display the adjacency list representation of the graph
  void printGraph();

  // Print the degree of all vertices
  void PrintDegree();

  // Fucntion to print all leaves in the tree
  void PrintLeaves();
  
  // Print the degree of all vertices with degree above n
  void PrintDegree_n(int n);
  
};

#endif  
  
