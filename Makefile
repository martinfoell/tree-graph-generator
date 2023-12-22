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
	pdflatex node.tex && \
	evince node.pdf

write:
	g++ ./test/write_vector.cpp  -o ./bin/write
	./bin/write

permutation:
	g++ ./test/permutation.cpp  -o ./bin/parmutation
	./bin/parmutation


pp:
	g++ ./test/perm.cpp  -o ./bin/parmutation2
	./bin/parmutation2

ppair:
	g++ ./test/permpair.cpp  -o ./bin/parmutation3
	./bin/parmutation3

order:
	g++ ./test/order.cpp  -o ./bin/order
	./bin/order

set:
	g++ ./test/set.cpp  -o ./bin/set
	./bin/set

saveperm:
	g++ ./test/saveperm.cpp  -o ./bin/saveperm
	./bin/saveperm

slice:
	g++ ./test/slice.cpp  -o ./bin/slice
	./bin/slice

compare:
	g++ ./test/compare.cpp  -o ./bin/compare
	./bin/compare

removedup:
	g++ ./test/removedup.cpp  -o ./bin/removedup
	./bin/removedup

removedup2:
	g++ ./test/removedup2.cpp  -o ./bin/removedup2
	./bin/removedup2



