adjlist:
	g++ ./test/adjlist.cpp -o ./bin/adjlist  -std=c++11
	./bin/adjlist 

partitions:
	g++ ./test/partitions.cpp -o ./bin/partitions  
	./bin/partitions

main:
	g++ ./test/main.cpp ./src/tree.cpp ./src/tikz.cpp ./src/utils.cpp ./src/layout.cpp -o ./bin/main2 
	./bin/main2

pdf-main:
	g++ ./test/main.cpp ./src/tree.cpp ./src/tikz.cpp ./src/utils.cpp ./src/layout.cpp -o ./bin/main2
	./bin/main2
	cd tex/ && \
	pdflatex node2.tex && \
	evince node2.pdf


