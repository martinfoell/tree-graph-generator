#include "../include/tikz.hpp"
#include "../include/utils.hpp"
#include <sstream>
// Constructor definition
Tikz::Tikz() {}

void Tikz::premable() {
  std::ofstream file("tex/premable.tex");  
  if (file.is_open()) {
    file << R"(\documentclass{article}
\usepackage[margin=0.5in,marginpar=0.75in]{geometry}
\usepackage{tikz}
\usetikzlibrary{calc}

\usepackage{ifthen}
\usepackage{fmtcount}



\makeatletter
\newcommand{\padnum}[2]{%
  \ifnum#1>1 \ifnum#2<10 0\fi
  \ifnum#1>2 \ifnum#2<100 0\fi
  \ifnum#1>3 \ifnum#2<1000 0\fi
  \ifnum#1>4 \ifnum#2<10000 0\fi
  \ifnum#1>5 \ifnum#2<100000 0\fi
  \ifnum#1>6 \ifnum#2<1000000 0\fi
  \ifnum#1>7 \ifnum#2<10000000 0\fi
  \ifnum#1>8 \ifnum#2<100000000 0\fi
  \ifnum#1>9 \ifnum#2<1000000000 0\fi
  \fi\fi\fi\fi\fi\fi\fi\fi\fi
  \expandafter\@firstofone\expandafter{\number#2}%
}
\makeatother

% Modulo command
\makeatletter
\newcommand{\modulo}[2]{%
  \number\numexpr#1-#2*(\number\numexpr(#1/#2)\relax)\relax
}
\makeatother

\newcommand{\checkNumberModulo}[2]{%
  \ifnum\modulo{#1}{#2}=0
    \par\vspace{1cm} % If number is multiple of the specified modulo
  \else
    \hspace{1cm} % If number is not a multiple
  \fi
}
)";
    file.close();
    }
}


void Tikz::tikzset(){
  std::ofstream file("tex/tikzset.tex");
  if (file.is_open()) {
    file << "\\tikzset{\n";
    file << "    every node/.style={\n";
    file << "        circle,\n";
    file << "        draw,\n";
    file << "        solid,\n";
    file << "        fill=black,\n";
    file << "        inner sep=0pt,\n";
    file << "        minimum width=4pt\n";
    file << "    }\n";
    file << "}\n";
    file.close();
  }
}

void Tikz::loop(){
  std::ofstream file("tex/loop.tikz");
  file << "\\foreach \\curr in \\numbers{\n";
  file << "  \\coordinate (\\curr) at ($ (\\prev) + (\\angle:1) $);\n";
  file << "  \\draw (\\prev) node {} -- (\\curr) node {};\n";
  file << "  \\xdef\\prev{\\curr} % Update the previous element to the current element\n";
  file << "}\n";
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

void Tikz::centralPath(std::string filename, int V, double angle){
  std::vector<int> numbers = createVector(0, V-1);
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
  file << "\\coordinate (\\prev) at (0, 0);\n";
  file << "\\foreach \\curr in \\numbers{\n";
  file << "  \\coordinate (\\curr) at ($ (\\prev) + (\\angle:1) $);\n";
  file << "  \\draw (\\prev) node {} -- (\\curr) node {};\n";
  file << "  \\xdef\\prev{\\curr} % Update the previous element to the current element\n";
  file << "}\n";
}


void Tikz::appendPath(int V, int L, int curr, int next, int length, int digits, int tree_index, double angle){
  // vector containing the numbers in the path
  size_t digits_size = static_cast<size_t>(digits);
  IntVector numbers = createVector(next, next + length - 1);
  // the index of the tree in the loop
  std::string index_old = std::to_string(tree_index+1);
  std::string index_new = std::string(digits_size - std::min(digits_size, index_old.length()), '0') + index_old;
  std::string filename = "tree_"+ index_new;

  std::string filePath = "tex/tikz/V" + std::to_string(V) + "/L" + std::to_string(L) + "/" + filename + ".tikz";
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

void Tikz::corePath(std::vector<int> numbers, double angle){
  std::ofstream file("tex/tikzCorepath.tikz");
  file << "\\def\\numbers{";
  for (size_t i = 1; i < numbers.size(); ++i) {
    file << numbers[i];
    if (i != numbers.size() - 1) {
      file << ",";
    }
  }
  file << "}\n";
  file << "\\def\\angle{"<< angle <<"}\n";  
}

void Tikz::makeTrees(int V, int L, int width, int digits, int n_trees) {
  // int digits_int = static_cast<int>(digits);    
  std::cout << "digits" << digits << std::endl;
  std::string filePath = "tex/tikz/V" + std::to_string(V) + "/L" + std::to_string(L) + "/input_trees.tex";
  std::cout << filePath << std::endl;
  std::ofstream File(filePath);
  if (File.is_open()) {
    std::ostringstream file;
    file << "\\foreach \\i in {1,...," << n_trees << "}{\n";
    file << "  \\begin{tikzpicture}[scale=0.3,baseline={(0,0)}]\n";
    file << "    \\input{central_tree.tikz}\n";
    // file << "    \\input{loop.tikz}\n";
    file << "    \\input{tikz/V" << V << "/L" << L << "/tree_\\padnum{" << digits << "}{\\i}.tikz}\n";
    file << "  \\end{tikzpicture}\n";
    file << "  \\checkNumberModulo{\\i}{" << width << "}\n";
    file << "}\n";
    
    File << file.str();
    File.close();
  }
}

bool Tikz::appendBody(int V, int L){
  std::ofstream file("tex/body.tex", std::ios::app);
  if (file.is_open()) {
    file << "\\input{tikz/V" << V << "/L" << L << "/input_trees}\n";        
    file.close();
    return true; // append successful
    } else {
    std::cout << "Unable to open file for appending.\n";
    return false; // append unsuccessful
  }
}


void Tikz::deleteBody(){
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string deletefile = pathAsString + "/tex/body.tex";
  try {
    if (std::filesystem::remove(deletefile))
       std::cout << "file " << deletefile << " deleted.\n";
    else
       std::cout << "file " << deletefile << " not found.\n";
  }
  catch(const std::filesystem::filesystem_error& err) {
     std::cout << "filesystem error: " << err.what() << '\n';
  }
}

void Tikz::writeMain() {
    std::ofstream file("main.tex");

    if (file.is_open()) {
        file << "\\input{preamble}\n";
        file << "\\begin{document}\n";
        file << "\\input{tikzset}\n";
        file << "\\input{body}\n";
        file << "\\end{document}\n";

        file.close();
    } else {
        std::cout << "Unable to open file for writing.\n";
    }
}

void Tikz::createDirectory(int V, int L) {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string vertexPath = mainDir + "/V" + std::to_string(V);  
  std::string leafPath = vertexPath + "/L" + std::to_string(L);
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


void Tikz::deleteTrees(int V, int L) {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string directoryPath = mainDir + "/V"+std::to_string(V) + "/L" + std::to_string(L);
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
  std::cout << "Deleted all files in " << "/tex/tikz/V"+std::to_string(V) + "/L" + std::to_string(L) << std::endl;
}
