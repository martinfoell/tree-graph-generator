adjlist:
	g++ ./test/adjlist.cpp -o ./bin/adjlist  -std=c++11
	./bin/adjlist 

partitions:
	g++ ./test/partitions.cpp -o ./bin/partitions  
	./bin/partitions

main:
	g++ ./test/main.cpp ./src/tree.cpp ./src/tikz.cpp -o ./bin/main2
	./bin/main2

write:
	g++ ./test/write_vector.cpp  -o ./bin/write
	./bin/write

