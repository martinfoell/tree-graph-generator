#include "../include/tree.hpp"


// Constructor definition
Tree::Tree(int vertices) {
    V = vertices;
    adjList.resize(V);
}

int Tree::emptyVertex(){
    // Find the first empty vector in adj
    int emptyVertex = -1;
    for (int i = 0; i < V; ++i) {
        if (adjList[i].empty()) {
            emptyVertex = i;
            break;
        }
    }
    return emptyVertex;
}

// Function to add an edge between vertex u and vertex v
void Tree::addEdge(int u, int v) {
    // For an undirected graph, add edges in both directions
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Tree::addNodeInbetween(int u, int v, int v_new)
{
  //add w in between u and v
  adjList[u].push_back(v_new);
  adjList[v_new].push_back(u);
  adjList[v].push_back(v_new);
  adjList[v_new].push_back(v);
  // remove edge betv_neween u and v
  adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
  adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
}

// adds a branch to a node u in a tree with length l starting from node v
void Tree::addPath(int curr, int next, int l){
  //add brach from u to next if they are not equal
  if (curr != next){
    adjList[curr].push_back(next);
    adjList[next].push_back(curr);
  }
  else if (curr == next){
    // need to combensate since u and next are the same
    l+=1;
  }
  //add branch from next to next+l
  for (int i = 0; i < l-1; i++){
    adjList[next+i].push_back(next + i + 1);
    adjList[next + i + 1].push_back(next + i);
  }
}

void Tree::addPaths(std::vector<int> nodes, std::vector<int> partion){
  // size of partition
  int n = partion.size();
  for (int i = 0; i < n; i++){
    // highest node that is empty
    int next = emptyVertex();
    // add branch to node
    addPath(nodes[i], next, partion[i]);
    next+=partion[i];
  }
}

// Function to display the adjacency list representation of the graph
void Tree::printGraph() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Adjacency list of vertex " << i << ":\n";
        std::cout << "head";
        for (int j = 0; j < adjList[i].size(); ++j) {
            std::cout << " -> " << adjList[i][j];
        }
        std::cout << std::endl;
    }
}


