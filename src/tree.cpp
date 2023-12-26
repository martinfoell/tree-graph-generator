#include "../include/tree.hpp"
#include "../include/utils.hpp"
#include "../include/layout.hpp"
#include "../include/tikz.hpp"


// Constructor definition
Tree::Tree(int vertices) {
    V = vertices;
    adjList.resize(V);
}

int Tree::degree(int vertex){
  return adjList[vertex].size();
}

int Tree::shortestPath(int source, int destination){
  std::vector<int> distance(V, INT_MAX);
  std::vector<bool> visited(V, false);
  std::queue<int> q;
  
  distance[source] = 0;
  visited[source] = true;
  q.push(source);
  
  while(!q.empty()){
    int u = q.front();
    q.pop();
    
    for(auto v : adjList[u]){
      if(!visited[v]){
	distance[v] = distance[u] + 1;
	visited[v] = true;
	q.push(v);
      }
    }
  }
  
  return distance[destination];
}

int Tree::diameter(){
  int max = 0;
  for(int i = 0; i < V; i++){
    for(int j = i+1; j < V; j++){
      int dist = shortestPath(i, j);
      if(dist > max){
	max = dist;
      }
    }
  }
  return max;
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


std::vector<int> Tree::leavesCentral(int V_central) {
    // find the leaves on the main path
    std::vector<int> leaves_central;
    if (V_central == 1){
      leaves_central = {0};
    }
    else if (V_central > 1){
      leaves_central = leaves();      
    }

    return leaves_central;

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

void Tree::addPaths(std::vector<int> vertices, std::vector<int> partion){
  // size of partition
  int n = partion.size();
  for (int i = 0; i < n; i++){
    // highest vertex that is empty
    int next = emptyVertex();
    // add branch to vertex
    addPath(vertices[i], next, partion[i]);
    next+=partion[i];
  }
}

void Tree::centralPath(int length){
  addPath(0, emptyVertex(), length-1);
}

void Tree::clear(){
  for (int i = 0; i < V; i++){
    adjList[i].clear();
  }
}

int Tree::generateTrees(Tree tree, int V, int L, int V_central, int width, int digits){

  Layout layout;
    
  Tikz tikz(V, L, V_central);
  tikz.createDirectory();    
  tikz.deleteTrees();
  tikz.centralPath(0);    
  
  Tree treeCentral(V); // create central tree
  treeCentral.centralPath(V_central);    
  std::vector<int> leaves_central = treeCentral.leavesCentral(V_central);
  int L_central = leaves_central.size();
  
  tree = treeCentral;        
  
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
	tikz.appendPath(leaf_central, last_vertex,  path[j], digits, k,  angles[j]);
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
  tikz.makeTrees(width, digits, paths.size());    
  tikz.appendTrees();

  return paths.size();
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


