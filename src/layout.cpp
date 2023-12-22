#include "../include/layout.hpp"

Layout::Layout() {
}

std::vector<double> Layout::angle(double angle, int n){
  std::vector<double> angles;
  angles.push_back(angle);
  double angle_step = 360/n;
  for (int i = 0; i < n-1; i++) {
		angle += angle_step;
		angles.push_back(angle);
  }
  return angles;
}

std::vector<double> Layout::left(double angle, int n){
  std::vector<double> angles;
  if (n == 2) {
    angles.push_back(angle+45);
    angles.push_back(angle+180-45);    
  }
  return angles;
}
