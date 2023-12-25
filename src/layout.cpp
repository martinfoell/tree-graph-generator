#include "../include/layout.hpp"

Layout::Layout() {
}

std::vector<double> Layout::angle(double angle, int n){
  std::vector<double> angles;
  int angle_init = angle;
  double angle_step = 360/n;
  for (int i = 0; i < n-1; i++) {
		angle += angle_step;
		angles.push_back(angle);
  }
  angles.push_back(angle_init);
  return angles;
}

std::vector<double> Layout::half(double angle1, double angle2, int V_central, int n, int rotation){
  std::vector<double> angles;
  if (V_central == 1) {
    std::cout << "this is working" << '\n';
    int angle_init = angle1;
    double angle_step = 360/n;
    for (int i = 0; i < n-1; i++) {
      angle1 += angle_step;
      angles.push_back(angle1);
    }
    angles.push_back(angle_init);
  }
  else if (n == 2) {
    std::cout << "this is NOT working" << '\n';
    angles.push_back(angle2 + rotation*45);
    angles.push_back(angle2 + rotation*180 - rotation*45);    
  }
  else if (n > 2) {
    std::cout << "this is NOT working" << '\n';
    double angle_step = 180/(n-1);
    for (int i = 0; i <= n; i++) {
      angles.push_back(angle2 + rotation*angle_step*i);
    }
  }
  return angles;
}
