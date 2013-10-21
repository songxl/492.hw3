#include "Sudoku.h"
#include <stdlib.h>

//--------------- Only Used in this File ---------------
void check_input(string cell) {
    if((cell.size() != 2) ||
       (Sudoku::row.find(cell[0]) == string::npos) ||
       (Sudoku::col.find(cell[1]) == string::npos)) {
        throw Error(Error::bad_input);
    }
}
//------------------------------------------------------






//------------ Static string initializations -----------
string Error::bad_parse("Something wrong with file  parsing");
string Error::bad_input("Invalid index");
string Sudoku::row("ABCDEFGHI");
string Sudoku::col("123456789");
//------------------------------------------------------






//------------------- Sudoku Methods -------------------
Sudoku::Sudoku(bool v) {
    valid = v;
}

Sudoku::Sudoku(string p, bool v) {
    valid = v;
    if(valid) {
	if(p.size() != 81)
	    throw Error(Error::bad_parse);
	for(int i=0; i<81; i++) {
	    if(!isdigit(p[i]))
		throw Error(Error::bad_parse);
	    string row_idx(1, row[i/9]);
	    string col_idx(1, col[i%9]);
	    string idx = row_idx + col_idx;
	    puzzle[idx] = p[i] - '0';
	}
    }
}

void Sudoku::print() {
    cout << "-------------------------" << endl;
    for(int i=0; i<9; i++) {
	cout << "| ";
	for(int j=0; j<9; j++) {
	    string row_idx(1, row[i]);
	    string col_idx(1, col[j]);
	    int val = puzzle[row_idx + col_idx];
	    if(val == 0) cout << ".";
	    else cout << val;
	    if(j!=8 && (j+1)%3==0)
		cout << " | ";
	    else
		cout << " ";
	}
	cout << "|" << endl;
	if(i!=8 && (i+1)%3==0)
	    cout << "--------+-------+--------" << endl;
    }
    cout << "-------------------------" << endl;
}

int& Sudoku::operator[](string idx) {
    check_input(idx);
    return puzzle[idx];
}
//------------------------------------------------------






//------------------- Puzzles Methods ------------------
Puzzles::Puzzles(string file) {
    ifile.open(file.c_str());
}

Sudoku Puzzles:: nextPuzzle() {
    string line;
    if(ifile >> line)
	return Sudoku(line);
    else
	return Sudoku(line, false);
}
//------------------------------------------------------






//------------------ Utility Functions -----------------
list<string> my_row(string cell) {
    check_input(cell);
    list<string> output;
    string row_idx(1, cell[0]);
    for(int c=0; c<9; c++) {
        if(Sudoku::col[c] != cell[1]) {
            string col_idx(1, Sudoku::col[c]);
            output.push_back(row_idx + col_idx);
        }
    }
    return output;
}

list<string> my_col(string cell) {
    check_input(cell);
    list<string> output;
    string col_idx(1, cell[1]);
    for(int r=0; r<9; r++) {
        if(Sudoku::row[r] != cell[0]) {
            string row_idx(1, Sudoku::row[r]);
            output.push_back(row_idx + col_idx);
        }
    }
    return output;
}

list<string> my_box(string cell) {
    check_input(cell);
    list<string> output;
    int ri = cell[0] - 'A';
    int ci = cell[1] - '1';
    for(int r=3*(ri/3); r<3*(ri/3)+3; r++) {
        for(int c=3*(ci/3); c<3*(ci/3)+3; c++) {
            if((Sudoku::row[r] != cell[0]) || (Sudoku::col[c] != cell[1])) {
                string row_idx(1, Sudoku::row[r]);
                string col_idx(1, Sudoku::col[c]);
                output.push_back(row_idx + col_idx);
            }
        }
    }
    return output;
}
//------------------------------------------------------
