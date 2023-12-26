adjlist:
	g++ ./test/adjlist.cpp -o ./bin/adjlist  -std=c++11
	./bin/adjlist 

partitions:
	g++ ./test/partitions.cpp -o ./bin/partitions  
	./bin/partitions

main:
	g++ ./test/main.cpp ./src/tree.cpp ./src/tex.cpp ./src/tikz.cpp ./src/utils.cpp ./src/layout.cpp -o ./bin/main2 
	./bin/main2

pdf-main:
	g++ ./test/main.cpp ./src/tree.cpp ./src/tex.cpp ./src/tikz.cpp ./src/utils.cpp ./src/layout.cpp -o ./bin/main2
	./bin/main2
	cd tex/ && \
	pdflatex main.tex && \
	evince main.pdf

delete:
	g++ -std=c++17 ./cpp_test/delete2.cpp  -o ./bin/delete2 
	./bin/delete2

printvector:
	g++ -std=c++17 ./test/printvector.cpp  -o ./bin/printvector 
	./bin/printvector

pp:
	g++ -std=c++17 ./test/pp.cpp  -o ./bin/pp 
	./bin/pp

filtervector:
	g++ -std=c++17 ./test/filtervector.cpp  -o ./bin/filtervector 
	./bin/filtervector
