#include <iostream>
#include <fstream>
#include <vector>


using IntVector = std::vector<int>;
using IntVector2D = std::vector<IntVector>;
using IntVector3D = std::vector<IntVector2D>;
using IntVector4D = std::vector<IntVector3D>;


class Tikz {
private:

public:
  Tikz();

  void premable();
  void begin();
  void end();  
  void tikzset();
  void loop();
  void inital(std::vector<int> numbers, double angle, double x, double y);
  void path(std::string filename, std::vector<int> numbers, double angle, double x, double y);
  // void addPath(std::string filename, int start_node, std::vector<int> numbers, double angle);
  void addPath(int V, int l,int curr, int next, int length, size_t digits, int tree_index, int path_index, double angle);  

  void addPathBkg(std::string filename, int start_node, std::vector<int> numbers, double angle);
  
  void corePath(std::vector<int> numbers, double angle);
  void inputTrees(int V, int width, size_t n_zero, int n_trees, int n_leaves);
  bool mainAppend(int V, int l);  
  // void inputTrees(int V, int width, int n_zero, int n_trees, int n_leaves);  
  

  
};


