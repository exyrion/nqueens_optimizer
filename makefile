puzzle: puzzle.o
	g++ puzzle.o -o puzzle
puzzle.o: puzzle.cpp
	g++ puzzle.cpp -c