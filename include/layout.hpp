#ifndef layout_hpp
#define layout_hpp

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




class Layout {
private:

public:
  // Constructor to initialize the graph with V vertices
  Layout();
  
  std::vector<double> angle(double angle, int n);
  // std::vector<double> left(double angle, int n);
  std::vector<double> half(double angle, int n, int rotation);  


  
};

#endif  
  
