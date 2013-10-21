

ac3: Sudoku.o ac3.cpp
	g++ -std=c++0x Sudoku.o ac3.cpp -o ac3

search: Sudoku.o search.cpp
	g++ -std=c++0x Sudoku.o search.cpp -o search

sudoku: Sudoku.cpp Sudoku.h
	g++ -std=c++0x -c Sudoku.cpp

clean:
	-rm ac3 search *.o *~