.PHONY: adjlist partitions main pdf-main delete printvector pp filtervector clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
BIN = bin

adjlist:
	$(CXX) $(CXXFLAGS) ./test/adjlist.cpp -o $(BIN)/adjlist
	./$(BIN)/adjlist

partitions:
	$(CXX) $(CXXFLAGS) ./test/partitions.cpp ./src/utils.cpp -o $(BIN)/partitions
	./$(BIN)/partitions

main:
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) ./test/main.cpp ./src/tree.cpp ./src/tex.cpp ./src/tikz.cpp ./src/utils.cpp ./src/layout.cpp -o $(BIN)/main2
	./$(BIN)/main2

pdf-main: main
	cd tex && pdflatex main.tex && EVINCE_DEBUG=0 evince main.pdf

printvector:
	$(CXX) $(CXXFLAGS) ./test/printvector.cpp ./src/utils.cpp -o $(BIN)/printvector
	./$(BIN)/printvector

pp:
	$(CXX) $(CXXFLAGS) ./test/pp.cpp ./src/utils.cpp -o $(BIN)/pp
	./$(BIN)/pp

filtervector:
	$(CXX) $(CXXFLAGS) ./test/filtervector.cpp ./src/utils.cpp -o $(BIN)/filtervector
	./$(BIN)/filtervector

clean:
	rm -rf $(BIN)/*
