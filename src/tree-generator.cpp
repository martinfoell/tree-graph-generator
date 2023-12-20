#include "../include/tree-generator.hpp"



class Tree {
  public:
  int n_;
  std::vector<std::vector<double>> A_;

  // Define the size of the matrix
  int rows = 3;
  int cols = 4;
  
  // Create a matrix (vector of vectors) and fill it with zeroes
  std::vector<std::vector<int>> matrix_(rows, std::vector<int>(cols, 0));
  
  // Display the matrix
  std::cout << "Matrix filled with zeroes:" << std::endl;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  // constructor
  Tree(int n);

  void add_node();

  void add_branch();
  
};
