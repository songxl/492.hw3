
#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

using namespace std;

/* Thrown in the case of an invalid index, or invalid data in the sudokus.txt file */
class Error {
  public:
    string msg;
    Error(string m) : msg(m) {}
    static string bad_parse;
    static string bad_input;
};


/* Class to hold a Sudoku. You may index an instance with the [] operator
 * e.g.       Sudoku sud = puz.nextPuzzle();
 *            int top_left_cell = sud["A1"];
 */
class Sudoku {
  private:
    map<string, int> puzzle;
  public:
    bool valid;
    Sudoku(bool v=true);
    Sudoku(string p, bool v=true);
    void print();
    int& operator[](string idx);
    static string row;
    static string col;
};


/* Class to handle reading the sudokus.txt file */
class Puzzles {
    ifstream ifile;
  public:
    Puzzles (string file);
    Sudoku nextPuzzle();
};



//------------------------------ Utility Functions ------------------------------

/* Returns a list of the indices in the same row as cell */
list<string> my_row(string cell);

/* Returns a list of the indices in the same column as cell */
list<string> my_col(string cell);

/* Returns a list of the indices in the same 3x3 box as cell */
list<string> my_box(string cell);




#endif //SUDOKU_H
