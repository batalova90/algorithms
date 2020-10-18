FC=g++
FOPT=-O3 -ftree-vectorize -fopt-info-vec

all: ./bin/app

./bin/app: ./obj/Tree.o ./obj/File_IO.o ./obj/main.o
	$(FC) $(FOPT) ./obj/main.o ./obj/File_IO.o ./obj/Tree.o -o ./bin/app

./obj/Tree.o: ./src/Tree.cpp ./src/Huffman_algorithm.h
	$(FC) $(FOPT) -c ./src/Tree.cpp -I ./obj -o ./obj/Tree.o
	
./obj/File_IO.o: ./src/File_IO.cpp ./src/Huffman_algorithm.h
	$(FC) $(FOPT) -c ./src/File_IO.cpp -I ./obj -o ./obj/File_IO.o

./obj/main.o: ./src/main.cpp ./src/Huffman_algorithm.h
	$(FC) $(FOPT) -c ./src/main.cpp -I ./obj -o ./obj/main.o

clean:
	rm -rf obj/*
	rm -rf bin/*

run:
	cd ./bin; ./app;
