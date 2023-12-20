#ifndef Tree_hpp
#define Tree_hpp

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
  public:
  int n_;
  std::vector<std::vector<double>> A_;
  
  // constructor
  Tree(int n);

  void add_node();

  void add_branch();
  
};



#endif  
  
