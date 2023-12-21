#include "../include/utils.hpp"
    
std::vector<int> createVector(int begin, int end){
  std::vector<int> vec(end-begin+1);
  // fills the vector from 1 to N
  std::iota(vec.begin(), vec.end(), begin);
  return vec;
}

void printVector(std::vector<int> vec){
  for (auto i : vec)
    std::cout << i << " ";
  std::cout << std::endl;
}
    // std::vector<int> vecw(3);

    // // fills the vector from 1 to N
    // std::iota(vecw.begin(), vecw.end(), 1);

    // for (auto i: vecw)
    //   std::cout << i << ' ';
    // std::cout << '\n';
