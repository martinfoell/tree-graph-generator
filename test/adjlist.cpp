// A simple representation of graph using Adjacent list
#include<iostream> 
#include<vector>
#include<map>
#include <algorithm>
using namespace std; 
  
// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u);
} 

void addNodeInbetween(vector<int> adj[], int u, int v, int w)
{
  //add w in between u and v
  adj[u].push_back(w);
  adj[w].push_back(u);
  adj[v].push_back(w);
  adj[w].push_back(v);
  // remove edge between u and v
  adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
  adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
}


int firstEmpty(vector<int> adj[], int V){
    // Find the first empty vector in adj
    int firstEmptyIndex = -1;
    for (int i = 0; i < V; ++i) {
        if (adj[i].empty()) {
            firstEmptyIndex = i;
            break;
        }
    }
    return firstEmptyIndex;
}



// adds a branch to a node u in a tree with length l starting from node v
void addBranch(vector<int> adj[], int u, int v, int l){
  //add brach from u to v if they are not equal
  if (u != v){
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  else if (u == v){
    // need to combensate since u and v are the same
    l+=1;
  }
  //add branch from v to v+l
  for (int i = 0; i < l-1; i++){
    adj[v+i].push_back(v + i + 1);
    adj[v + i + 1].push_back(v + i);
  }
}

void addBranches(vector<int> adj[], int V, std::vector<int> nodes, std::vector<int> partion){
  // size of partition
  int n = partion.size();
  for (int i = 0; i < n; i++){
    // highest node that is empty
    int count = firstEmpty(adj, V);
    // add branch to node
    addBranch(adj, nodes[i], count, partion[i]);
    count+=partion[i];
  }
}

void initalizeTree_simple(vector<int> adj[], int m){
  for (int i = 0; i < m - 1; i++){
    addEdge(adj, i, i+1);
  }
}

std::vector<int> leaves(vector<int> adj[], int n){
  std::vector<int> leaves_;
  for(int i=0;i<n;i++){
    if(adj[i].size()==1){
      leaves_.push_back(i);
    }
  }
  return leaves_;
}

void PrintLeaves(vector<int> adj[], int n){
	std::vector<int> leaves_ = leaves(adj,n);
	std::cout<<"Number of leaves: "<<leaves_.size()<<std::endl;
	for(int i=0;i<leaves_.size();i++){
	  std::cout<<"Vertex "<<leaves_[i]<<" is a leaf"<<std::endl;
	  // std::cout<<leaves_[i]<<" ";
	}
	std::cout<<std::endl;

}

int degree(vector<int> adj[], int v){
  return adj[v].size();
}

void PrintDegree(vector<int> adj[], int n){
	std::cout<<"Degree of each vertex: "<<std::endl;
	for(int i=0;i<n;i++){
		std::cout<<"Vertex "<<i<<" has degree "<<degree(adj,i)<<std::endl;
	}
}


// map with key as vertex and value as degree above n
std::map<int,int> degree_n(vector<int> adj[], int v, int n){
	std::map<int,int> degree_map;
	for(int i = 0; i < v; i++){
	  if(degree(adj, i) > n){
	    degree_map[i] = degree(adj, i);
	  }
	}
	
	return degree_map;
}

// Printing map with key as vertex and value as degree above n
void PrintDegree_n(vector<int> adj[], int v,int n){
  std::map<int,int> degree_n_ = degree_n(adj,v,n);
  std::cout<<"Number of vertices with degree above "<< n << ": "<< degree_n_.size() <<std::endl;
  for(auto it = degree_n_.begin(); it != degree_n_.end(); ++it){
		std::cout<<"Vertex "<<it->first<<" has degree "<<it->second<<std::endl;
	}
}

std::vector<int> shortest_path(vector<int> adj[], int v, int u){
	std::vector<int> path;
	path.push_back(u);
	while(path.back() != v){
		for(int i = 0; i < adj[path.back()].size(); i++){
			if(adj[path.back()][i] < path.back()){
				path.push_back(adj[path.back()][i]);
				break;
			}
		}
	}
	return path;
}


// A utility function to print the adjacency list 
// representation of graph 
void printGraph(vector<int> adj[], int V) 
{ 
  vector<int>::iterator it;
  for (int v = 0; v < V; ++v) 
    { 
      cout << "\n Adjacency list of vertex "
	   << v << "\n head "; 
      for (it=adj[v].begin();it!=adj[v].end();it++) 
	cout << "-> " <<*it; 
      printf("\n"); 
    } 
} 

// Driver code 
int main() 
{ 
    int V = 13; 
    vector<int> adj[V]; 
    // initalizeTree_simple(adj,1);
    std::cout<<firstEmpty(adj,V)<<std::endl;
    // addBranch(adj, 0, 1, 2);
    addBranches(adj,V, {0,0,0}, {4,3,2});
    // addBranches(adj,V, {0}, {4});
    // addBranches(adj,V, {0}, {3});
    // addBranches(adj,V, {0}, {2});        
    
    // addEdge(adj, 0, 2);
    // addEdge(adj, 0, 3);
    // addEdge(adj, 1, 4);
    // addEdge(adj, 1, 5);
    // addNodeInbetween(adj,0,1,6);
    
    // std::cout << adjSize(adj) << std::endl;
    // addBranch(adj,1,2,2);
    // addEdge(adj, 0, 1); 
    // addEdge(adj, 0, 4); 
    // addEdge(adj, 1, 2); 
    // addEdge(adj, 1, 3); 
    // addEdge(adj, 1, 4); 
    // addEdge(adj, 2, 3); 
    // addEdge(adj, 3, 4); 
    printGraph(adj, V);
    std::cout<<"First empty: "<<firstEmpty(adj,V)<<std::endl;
    std::cout<<degree(adj, 1)<<std::endl;
    // std::cout<< "nodes with degree over 2; " << degree_n(adj, 2)<<std::endl;
    std::cout << adj[0][1] << std::endl;
    degree_n(adj, V, 2);
    PrintDegree(adj, V);
    PrintDegree_n(adj, V, 2);
    PrintLeaves(adj, V);
    return 0; 
} 






