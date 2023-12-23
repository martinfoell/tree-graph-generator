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

std::vector<double> Layout::half(double angle, int n, int rotation){
  std::vector<double> angles;
  if (n == 2) {
    angles.push_back(angle + rotation*45);
    angles.push_back(angle + rotation*180 - rotation*45);    
  }
  else if (n > 2) {
    double angle_step = 180/(n-1);
    for (int i = 0; i <= n; i++) {
      angles.push_back(angle + rotation*angle_step*i);
    }
  }
  return angles;
}
