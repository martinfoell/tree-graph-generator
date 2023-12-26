#ifndef tex_hpp
#define tex_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class Tex {
public:
  Tex();

  void premable();
  void tikzset();
  void tikzloop();
  void writeMain();
  void deleteBody();

};
#endif
