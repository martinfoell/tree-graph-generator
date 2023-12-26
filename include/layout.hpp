#ifndef layout_hpp
#define layout_hpp

#include <vector>
#include <iostream>



class Layout {
private:

public:
  // Constructor to initialize the graph with V vertices
  Layout();
  
  std::vector<double> angle(double angle, int n);
  // std::vector<double> left(double angle, int n);
  std::vector<double> half(double angle1, double angle2, int V_central, int n, int rotation);
  std::vector<double> half(double angle1, double angle2, int n, int rotation);
  // std::vector<double> half(double angle, int n, int rotation);  


  
};

#endif  
  
