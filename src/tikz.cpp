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

void Tikz::begin() {
  std::ofstream file("tex/end.tex");  
  if (file.is_open()) {
    file << R"(
\begin{document})";
    file.close();
  }
}

void Tikz::end() {
  std::ofstream file("tex/end.tex");  
  if (file.is_open()) {
    file << R"(
\end{document})";
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
}

void Tikz::addPath(int V, int l,int curr, int next, int length, size_t digits, int tree_index, int path_index, double angle){
  // vector containing the numbers in the path
  IntVector numbers = createVector(next, next + length - 1);
  // the index of the tree in the loop
  std::string index_old = std::to_string(tree_index+1);
  std::string index_new = std::string(digits - std::min(digits, index_old.length()), '0') + index_old;
  std::string filename = "path_"+ index_new + "_" + std::to_string(path_index);

  std::string filePath = "tex/tikz/n" + std::to_string(V) + "/l" + std::to_string(l) + "/" + filename + ".tikz";
  std::ofstream file(filePath);
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
}

void Tikz::addPathBkg(std::string filename, int start_node, std::vector<int> numbers, double angle){
  std::string filePath = "tex/tikz/" + filename + ".tikz";
  std::ofstream file(filePath);
  file << "\\def\\prev{"<< start_node <<"}\n";
  file << "\\def\\numbers{";
  for (size_t i = 0; i < numbers.size(); ++i) {
    file << numbers[i];
    if (i != numbers.size() - 1) {
      file << ",";
    }
  }
  file << "}\n";
  file << "\\def\\angle{"<< angle <<"}\n";
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

void Tikz::inputTrees(int V, int width, size_t digits, int n_trees, int n_leaves) {
  int digits_int = static_cast<int>(digits);    
  std::string zero(digits_int,'0');
  std::string filePath = "tex/tikz/n" + std::to_string(V) + "/l" + std::to_string(n_leaves) + "/input_trees.tex";
  std::ofstream File(filePath);
  if (File.is_open()) {
    std::ostringstream file;
    file << "\\foreach \\i in {1,...," << n_trees << "}{\n";
    file << "  \\begin{tikzpicture}[scale=0.3,baseline={(0,0)}]\n";
    file << "    \\input{core.tikz}\n";
    file << "    \\input{loop.tikz}\n";
    file << "    \\foreach \\j in {1,...," << n_leaves << "}{\n";
    file << "      \\input{tikz/path_\\padnum{" << digits_int << "}{\\i}_\\j.tikz}\n";
    file << "      \\input{loop.tikz}\n";
    file << "    }\n";
    file << "  \\end{tikzpicture}\n";
    file << "  \\checkNumberModulo{\\i}{" << width << "}\n";
    file << "}\n";
    
    File << file.str();
    File.close();
  }
}

bool Tikz::mainAppend(int V, int l){
  std::ofstream file("body.tex", std::ios::app);
  if (file.is_open()) {
    file << "\\input{tikz/n" << V << "/l" << l << "/input_trees}\n";        
    file.close();
    return true; // append successful
    } else {
    std::cout << "Unable to open file for appending.\n";
    return false; // append unsuccessful
  }
}
