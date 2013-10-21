#include "Sudoku.h"
#include <queue>

using namespace std;
map <string, queue<int> *> domain_map;
bool solvable;

Sudoku my_sud;
bool ac3();
void ac3_helper(string index);
bool backtracking_search();
bool backtrack_helper();
bool succeed;
//int min_queue_length = 1; //starting from 1

bool backtracking_search(){

	bool finished;	//first run
	finished = backtrack_helper();
	
	if (finished) {
		return true;
	}
}

bool backtrack_helper(){

	if (ac3()) { return true;}
	int min_queue_length = 2;
	while(min_queue_length < 10){
	//my_sud.print();
	bool find_min = false;
		for(int i=0; i<81; i++) {
			
			string row_idx(1, my_sud.row[i/9]);
			string col_idx(1, my_sud.col[i%9]);
			string index = row_idx + col_idx;
			//run the ac3 algorithm
			if (my_sud[index] != 0) {continue;}
			/*
			cout << "index "<< index<<endl;
			cout << "domain_map[index]->size() "<< domain_map[index]->size() << endl;
			cout << "min_queue_length "<< min_queue_length << endl;
			*/
			if (domain_map[index]->size() == min_queue_length){
				find_min = true;
				while(!domain_map[index]->empty() && my_sud[index] == 0)
				{
					cout << "MKV run size " << domain_map[index]->size() <<endl;
					Sudoku this_try_temp= my_sud;	
					my_sud[index] = domain_map[index]->front();
					domain_map[index]->pop();
					bool succeed = ac3();
					if (succeed) {//my_sud has been updated;
						return true;
					}
					
					if (solvable == true){
						cout << "new helper \n";
						succeed = backtrack_helper();
					}
					
					if (solvable == false){
						cout << "false, stash, next"<<endl;
						my_sud = this_try_temp;	//remove inference
						solvable = true;
					}
				}
				//find_min = false;	
			}

		}
		if (find_min == false) { cout << "no min "<< min_queue_length<< endl;}
		if (find_min == false) {min_queue_length ++;}		
	}
	
	return false;

}

bool ac3() {
	solvable = true;

	for(int i=0; i<81; i++) {
		string row_idx(1, my_sud.row[i/9]);
		string col_idx(1, my_sud.col[i%9]);
		string index = row_idx + col_idx;
		//run the ac3 algorithm
		if (my_sud[index] == 0)
			ac3_helper(index);
		
	}
	bool solved = true;
	for(int i=0; i<81; i++) {
		string row_idx(1, my_sud.row[i/9]);
		string col_idx(1, my_sud.col[i%9]);
		string index = row_idx + col_idx;
		//run the ac3 algorithm
		solved  = (my_sud [index] == 0)?false:solved ; 
		
	}
	
	return solved;
}

void ac3_helper(string index){
		
		if (solvable == false) {
			return;
		}
		//run the ac3 algorithm
		if (domain_map.find(index) == domain_map.end()){
		//first time visiting this cell, make the domain queue for it
			queue<int> *domain_q = new queue<int>;

			for (int i = 1; i < 10; i ++){
				domain_q->push(i);

			}
			domain_map.insert(pair<string, queue<int> *> (index, domain_q));

		}	
		int domain_size = domain_map[index]->size();

		list<string>::iterator it;

		for (int i = 0; i < domain_size; i++){
		//iterate every domain element
			bool popped = false;
			int possible_digit = domain_map[index]->front();
			domain_map[index]->pop();
			// compare the digit with all it's related cells
			list <string> curr_row = my_row(index);
			for (it = curr_row.begin(); it != curr_row.end(); ++it){
				if (possible_digit == my_sud[*it]){
					//cout << index<<  " pop "<<possible_digit<< endl;
					popped = true;
					break;
				}
			}

			list <string> curr_col = my_col(index);
			for (it = curr_col.begin(); it != curr_col.end(); it++){
				if (possible_digit == my_sud[*it]){
				//cout << index<<  " pop "<<possible_digit<< endl;
					popped = true;
					break;
				}
			}

			list <string> curr_box = my_box(index);
			for (it = curr_box.begin(); it != curr_box.end(); it++){
				if (possible_digit == my_sud[*it]){			
					//cout << index<<  " pop "<<possible_digit<< endl;
					popped = true;
					break;
				}
			}

			if (popped == false){
				//this digit is possible answer,push to the back of the queue
				domain_map[index]->push(possible_digit);
			}
		}
	//cout << "on index: "<< index<< " only choice is "<< domain_map[index]->front()<<endl;
		if (domain_map[index]->size() > 1){
		//may or may not shrinked the domain, but done with this cell
			//cout << index << "remains " << domain_map.find(index)->second->size()<<endl;
			return;
		}
		if (domain_map[index]->size() == 0){
		//falsed on this puzzle
			//cout << "domain = 0!\n";
			solvable = false;
			return;
		}
		
		
		if (domain_map[index]->size() == 1){

		//shrinked the domain to one possible answer;
			//write the asnwer to thepuzzle
			//cout << "on index: "<< index<< "only choice is "<< domain_map[index]->front()<<endl;
			my_sud[index] = domain_map[index]->front();
			//my_sud.print();
			//for every other related cells, recheck
			list <string> curr_row = my_row(index);
			for (it = curr_row.begin(); it != curr_row.end(); it++){
				if (my_sud[*it] == 0){
					ac3_helper(*it);
				}
			}	
			list <string> curr_col = my_col(index);
			for (it = curr_col.begin(); it != curr_col.end(); it++){
				if (my_sud[*it] == 0){
					ac3_helper(*it);
				}
			}
			list <string> curr_box = my_box(index);
			for (it = curr_box.begin(); it != curr_box.end(); it++){
				if (my_sud[*it] == 0){
					ac3_helper(*it);
				}
			}
		
		}

		return;
}

int main() {
    Puzzles puz("sudokus.txt");
    Sudoku sud = puz.nextPuzzle();
   // sud.print();
		//make it global
	int count = 0;
    while(sud.valid) 
    {
		my_sud = sud; 
		domain_map.clear();
		succeed = backtracking_search();
		if (succeed) { 
			count ++; 
			my_sud.print();
		}
		//If it's solveable, print solution
		    sud = puz.nextPuzzle();
    }
		cout << "count " <<count <<endl;
    return 0;
}
