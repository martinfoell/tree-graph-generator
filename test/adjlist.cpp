// A simple representation of graph using Adjacent list
#include<iostream> 
#include<vector>
#include<map>
using namespace std; 
  
// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
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
	for(int i=0;i<leaves_.size();i++){
	  std::cout<<"Vertex "<<leaves_[i]<<" is a leaf";
	  // std::cout<<leaves_[i]<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"Number of leaves: "<<leaves_.size()<<std::endl;
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
  std::cout<< degree_n_.size() <<" vertices have degree greater than "<<n<<std::endl;
  std::cout<<"Degree of each vertex above: "<< n <<std::endl;
  for(auto it = degree_n_.begin(); it != degree_n_.end(); ++it){
		std::cout<<"Vertex "<<it->first<<" has degree "<<it->second<<std::endl;
	}
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
    int V = 5; 
    vector<int> adj[V]; 
    // addEdge(adj, 0, 1); 
    addEdge(adj, 0, 4); 
    addEdge(adj, 1, 2); 
    addEdge(adj, 1, 3); 
    addEdge(adj, 1, 4); 
    addEdge(adj, 2, 3); 
    addEdge(adj, 3, 4); 
    printGraph(adj, V);
    std::cout<<degree(adj, 1)<<std::endl;
    // std::cout<< "nodes with degree over 2; " << degree_n(adj, 2)<<std::endl;
    std::cout << adj[0][1] << std::endl;
    degree_n(adj, V, 2);
    PrintDegree(adj, V);
    PrintDegree_n(adj, V, 2);
    PrintLeaves(adj, V);
    return 0; 
} 






