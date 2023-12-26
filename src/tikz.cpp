#include "../include/tikz.hpp"
#include "../include/utils.hpp"
#include <sstream>

Tikz::Tikz(int V, int L, int V_central) {
  V_ = V;
  L_ = L;
  V_central_ = V_central;
}

void Tikz::path(std::string filename, std::vector<int> numbers, double angle, double x, double y){
  std::string filePath = "tex/" + filename + ".tikz";
  std::ofstream file(filePath);
  file << "\\def\\prev{"<< numbers[0]<<"}\n";
  file << "\\def\\numbers{";
  for (size_t i = 1; i < numbers.size(); ++i) {
    file << numbers[i];
    if (i != numbers.size() - 1) {
      file << ",";
    }
  }
  file << "}\n";
  file << "\\def\\angle{"<< angle <<"}\n";
  file << "\\coordinate (\\prev) at ("<< x <<","<< y <<");\n";
  file << "\\foreach \\curr in \\numbers{\n";
  file << "  \\coordinate (\\curr) at ($ (\\prev) + (\\angle:1) $);\n";
  file << "  \\draw (\\prev) node {} -- (\\curr) node {};\n";
  file << "  \\xdef\\prev{\\curr} % Update the previous element to the current element\n";
  file << "}\n";
}

void Tikz::centralPath(double angle){
  std::vector<int> numbers = createVector(0, V_central_ - 1);
  std::string filePath = "tex/tikz/V" + std::to_string(V_) + "/V_C" + std::to_string(V_central_) + "/central_tree.tikz";
  std::ofstream file(filePath);
  file << "\\def\\prev{"<< numbers[0]<<"}\n";
  file << "\\def\\numbers{";
  for (size_t i = 1; i < numbers.size(); ++i) {
    file << numbers[i];
    if (i != numbers.size() - 1) {
      file << ",";
    }
  }
  file << "}\n";
  file << "\\def\\angle{"<< angle <<"}\n";
  file << "\\coordinate (\\prev) at (0, 0);\n";
  file << "\\foreach \\curr in \\numbers{\n";
  file << "  \\coordinate (\\curr) at ($ (\\prev) + (\\angle:1) $);\n";
  file << "  \\draw (\\prev) node {} -- (\\curr) node {};\n";
  file << "  \\xdef\\prev{\\curr} % Update the previous element to the current element\n";
  file << "}\n";
}


void Tikz::appendPath(int curr, int next, int length, int digits, int tree_index, double angle){
  // vector containing the numbers in the path
  size_t digits_size = static_cast<size_t>(digits);
  IntVector numbers = createVector(next, next + length - 1);
  // the index of the tree in the loop
  std::string index_old = std::to_string(tree_index+1);
  std::string index_new = std::string(digits_size - std::min(digits_size, index_old.length()), '0') + index_old;
  std::string filename = "tree_"+ index_new;

  std::string filePath = "tex/tikz/V" + std::to_string(V_) + "/V_C" + std::to_string(V_central_)+ "/L" + std::to_string(L_) + "/" + filename + ".tikz";
  std::ofstream file(filePath, std::ios::app);
  file << "\\def\\prev{"<< curr <<"}\n";
  file << "\\def\\numbers{";
  for (size_t i = 0; i < numbers.size(); ++i) {
    file << numbers[i];
    if (i != numbers.size() - 1) {
      file << ",";
    }
  }
  file << "}\n";
  file << "\\def\\angle{"<< angle <<"}\n";
  file << "\\input{loop.tikz}\n";
  
  file.close();
}


void Tikz::makeTrees(int width, int digits, int n_trees) {
  // int digits_int = static_cast<int>(digits);    
  std::cout << "digits" << digits << std::endl;
  std::string texfolderPath = "tex/";
  std::string tikzfolderPath = "tikz/V" + std::to_string(V_) + "/V_C" + std::to_string(V_central_) + "/L" + std::to_string(L_) + "/";
  std::string tikzfolderPath2 = "tikz/V" + std::to_string(V_) + "/V_C" + std::to_string(V_central_) + "/";  
  std::string texPath = texfolderPath + tikzfolderPath + "input_trees.tex";
  std::string tikzPath = tikzfolderPath2 + "central_tree.tikz";
  // std::string filePath = "tex/tikz/V" + std::to_string(V) + "/L" + std::to_string(L) + "/input_trees.tex";
  std::cout << texfolderPath + tikzfolderPath << std::endl;
  std::cout << texPath << std::endl;
  std::cout << tikzPath << std::endl;
  std::ofstream File(texPath);
  if (File.is_open()) {
    std::ostringstream file;
    file << "\\foreach \\i in {1,...," << n_trees << "}{\n";
    file << "  \\begin{tikzpicture}[scale=0.3,baseline={(0,0)}]\n";
    file << "    \\input{" << tikzPath << "}\n";
    file << "    \\input{tikz/V" << V_ <<  "/V_C" << V_central_ << "/L" << L_ << "/tree_\\padnum{" << digits << "}{\\i}.tikz}\n";
    file << "  \\end{tikzpicture}\n";
    file << "  \\checkNumberModulo{\\i}{" << width << "}\n";
    file << "}\n";
    
    File << file.str();
    File.close();
  }
}

bool Tikz::appendTrees(){
  std::ofstream file("tex/body.tex", std::ios::app);
  if (file.is_open()) {
    file << "\\input{tikz/V" << V_ << "/V_C" << V_central_ << "/L" << L_ << "/input_trees}\n";        
    file.close();
    return true; // append successful
    } else {
    std::cout << "Unable to open file for appending.\n";
    return false; // append unsuccessful
  }
}



void Tikz::createDirectory() {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string vertexPath = mainDir + "/V" + std::to_string(V_);
  std::string centralTreePath = vertexPath + "/V_C" + std::to_string(V_central_);
  std::string leafPath = centralTreePath + "/L" + std::to_string(L_);
  // Check if the directory already exists
  if (!fs::exists(vertexPath)) {
    // Create the directory
    if (fs::create_directory(vertexPath)) {
      std::cout << "Directory created successfully!" << std::endl;
    } else {
      std::cout << "Failed to create directory!" << std::endl;
    }
  } else {
    std::cout << "Directory already exists!" << std::endl;
  }
  if (!fs::exists(centralTreePath)) {
    // Create the directory
    if (fs::create_directory(centralTreePath)) {
      std::cout << "Directory created successfully!" << std::endl;
    } else {
      std::cout << "Failed to create directory!" << std::endl;
    }
  } else {
    std::cout << "Directory already exists!" << std::endl;
  }
  if (!fs::exists(leafPath)) {
    // Create the directory
    if (fs::create_directory(leafPath)) {
      std::cout << "Directory created successfully!" << std::endl;
    } else {
      std::cout << "Failed to create directory!" << std::endl;
    }
  } else {
    std::cout << "Directory already exists!" << std::endl;
  }
}


void Tikz::deleteTrees() {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string directoryPath = mainDir + "/V"+std::to_string(V_) + "/V_C"+std::to_string(V_central_) + "/L" + std::to_string(L_);
  try {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.path())) {
	fs::remove(entry.path());
	// std::cout << "Deleted: " << entry.path().string() << std::endl;
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  std::cout << "Deleted all files in " << "/tex/tikz/V"+std::to_string(V_) + "/V_C" + std::to_string(V_central_) +"/L" + std::to_string(L_) << std::endl;
}
