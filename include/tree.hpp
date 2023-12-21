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

  // Function to find the first empty vertex in the adjacency list
  int emptyVertex();
  
  // Function to add an edge between vertex u and vertex v
  void addEdge(int u, int v);

  // Function to add a new vertex between vertex u and vertex v
  void addNodeInbetween(int u, int v, int v_new);

  // Function to add a path from a curent nude to the next and so on with length l
  void addPath(int curr, int next, int l);

  // Function to add a path from a set of nodes into a set of partitions
  void addPaths(std::vector<int> nodes, std::vector<int> partion);
  
  // Function to display the adjacency list representation of the graph
  void printGraph();
};

#endif  
  
