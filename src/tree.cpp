#include "../include/tree.hpp"


// Constructor definition
Tree::Tree(int vertices) {
    V = vertices;
    adjList.resize(V);
}

int Tree::degree(int v){
  return adjList[v].size();
}

// map with key as vertex and value as degree above n
std::map<int,int> Tree::degree_n(int n){
  std::map<int,int> degree_map;
  for(int i = 0; i < V; i++){
    if(degree(i) > n){
      degree_map[i] = degree(i);
    }
  }
  return degree_map;
}

std::vector<int> Tree::leaves(){
  std::vector<int> leaves_;
  for(int i=0;i<V;i++){
    if(adjList[i].size()==1){
      leaves_.push_back(i);
    }
  }
  return leaves_;
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
void Tree::addPath(int curr, int next, int length){
  //add brach from u to next if they are not equal
  if (curr != next){
    adjList[curr].push_back(next);
    adjList[next].push_back(curr);
  }
  else if (curr == next){
    // need to combensate since u and next are the same
    length+=1;
  }
  //add branch from next to next+l
  for (int i = 0; i < length-1; i++){
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

void Tree::corePath(int l){
  addPath(0, emptyVertex(), l-1);
}

void Tree::clear(){
  for (int i = 0; i < V; i++){
    adjList[i].clear();
  }
}
//////// Print functions ////////


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

void Tree::PrintDegree(){
  std::cout<<"Degree of each vertex: "<<std::endl;
  for(int i=0;i<V;i++){
    std::cout<<"Vertex "<<i<<" has degree "<<degree(i)<<std::endl;
  }
}

// Printing map with key as vertex and value as degree above n
void Tree::PrintDegree_n(int n){
  std::map<int,int> degree_n_ = degree_n(n);
  std::cout<<"Number of vertices with degree above "<< n << ": "<< degree_n_.size() <<std::endl;
  for(auto it = degree_n_.begin(); it != degree_n_.end(); ++it){
		std::cout<<"Vertex "<<it->first<<" has degree "<<it->second<<std::endl;
	}
}

void Tree::PrintLeaves(){
  std::vector<int> leaves_ = leaves();
  std::cout<<"Number of leaves: "<<leaves_.size()<<std::endl;
  for(int i=0;i<leaves_.size();i++){
    std::cout<<"Vertex "<<leaves_[i]<<" is a leaf"<<std::endl;
  }
  std::cout<<std::endl;
}


