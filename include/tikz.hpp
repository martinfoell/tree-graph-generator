#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using IntVector = std::vector<int>;
using IntVector2D = std::vector<IntVector>;
using IntVector3D = std::vector<IntVector2D>;
using IntVector4D = std::vector<IntVector3D>;


class Tikz {

protected:
  int V_, L_, V_central_;
  

public:
  Tikz(int V, int L, int V_central);

  void inital(std::vector<int> numbers, double angle, double x, double y);
  void path(std::string filename, std::vector<int> numbers, double angle, double x, double y);
  
  void centralPath(double angle);

  void appendPath(int curr, int next, int length, int digits, int tree_index, double angle);  
  
  void makeTrees(int width, int digits, int n_trees);  
  bool appendTrees();  
  
  bool mainAppend(int V, int L);
  
  void createDirectory();    
  void deleteTrees();  
  
};


