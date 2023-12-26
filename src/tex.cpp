#include "../include/tex.hpp"

Tex::Tex() {}

void Tex::premable() {
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


void Tex::tikzset(){
  std::ofstream file("tex/tikzset.tex");
  if (file.is_open()) {
    file << "\\tikzset{\n";
    file << "    every node/.style={\n";
    file << "        circle,\n";
    file << "        draw,\n";
    file << "        solid,\n";
    file << "        fill=black,\n";
    file << "        inner sep=0pt,\n";
    file << "        minimum width=3pt\n";
    file << "    }\n";
    file << "}\n";
    file.close();
  }
}


  
 
void Tex::tikzloop(){
  std::ofstream file("tex/loop.tikz");
  file << "\\foreach \\curr in \\numbers{\n";
  file << "  \\coordinate (\\curr) at ($ (\\prev) + (\\angle:1) $);\n";
  file << "  \\draw (\\prev) node {} -- (\\curr) node {};\n";
  file << "  \\xdef\\prev{\\curr} % Update the previous element to the current element\n";
  file << "}\n";
}

void Tex::deleteBody(){
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

 void Tex::writeMain(){
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
 

