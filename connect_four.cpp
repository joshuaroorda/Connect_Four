#include <iostream>
#include <string>

/*
Made by: Joshua Roorda
Date: February 2019
*/

/*known bugs:
none
*/

/* DEBUG
std::cout << "i: " << i << std::endl;
std::cout << "j: " << j << std::endl;
std::cout << "num_tokens: " << num_tokens << std::endl;
std::cout << "tmp: " << tmp << std::endl;
std::cout << "tmp_two: " << tmp_two << std::endl;
std::cout << "O_block: " << O_block << std::endl;
std::cout << "X_win: " << X_win << std::endl;
*/

struct space {

	int identity{ 0 };

	space* p_right{ nullptr };
	space* p_right_down{ nullptr };
	space* p_down{ nullptr };
	space* p_left_down{ nullptr };
	space* p_left{ nullptr };
	space* p_left_up{ nullptr };
	space* p_up{ nullptr };
	space* p_right_up{ nullptr };

};

int main();
void create_board(space board[6][7]); // links the connect four spaces together for computer to see
void print_board(space board[6][7]); // prints the board to the console
bool insert(space board[6][7], int col, bool is_x, bool print); // inserts token into board, returns false for invalid input
void undo(space board[6][7], int col); // remove the top token from a column
bool is_won(space board[6][7]); // see if the game is won 
bool is_won(space board[6][7], int prev); // see if the game is won using pointers (using this!!!)
int can_win(space board[6][7], int id); // returns id's winning move (if one exists), else, return 7
int scenario(space board[6][7], int i, int j, int tmp, int tmp_two, int diag, int scen_id, bool using_tmp, bool O_block, bool X_win);
int triple_scenarios(space board[6][7], int tmp, int tmp_two, int i, int j, int diag, bool O_block, bool X_win); // go through the scenarios present in creating triple scenarios
int three_in_sequence(space board[6][7], int id, bool O_block, bool X_win); // return a move that will give id three in sequence (with space in middle or on edge)
int two_in_sequence(space board[6][7], int id, bool O_block, bool X_win); // return a move that will give id two tokens right next to each other
int row_tokens(space board[6][7], int row); // returns the number of tokens in a row
int computer_move(space board[6][7]); // returns the column of the computers move
void two_player_game(); // two player option
void one_player_game(); // one player option


void create_board(space board[6][7]) {

	//link p_rights
	for (int i{ 0 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 5; ++j) {

			board[i][j].p_right = &board[i][j + 1];
			
		}
	}
	
	//link p_lefts
	for (int i{ 0 }; i <= 5; ++i) {
		for (int j{ 1 }; j <= 6; ++j) {

			board[i][j].p_left = &board[i][j - 1];

		}
	}

	//link p_ups
	for (int i{ 1 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 6; ++j) {

			board[i][j].p_up = &board[i - 1][j];

		}
	}

	//link p_downs
	for (int i{ 0 }; i <= 4; ++i) {
		for (int j{ 0 }; j <= 6; ++j) {

			board[i][j].p_down = &board[i + 1][j];

		}
	}

	//link p_right_downs
	for (int i{ 0 }; i <= 4; ++i) {
		for (int j{ 0 }; j <= 5; ++j) {

			board[i][j].p_right_down = &board[i + 1][j + 1];

		}
	}

	//link p_right_ups
	for (int i{ 1 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 5; ++j) {

			board[i][j].p_right_up = &board[i - 1][j + 1];

		}
	}

	//link p_left_downs
	for (int i{ 0 }; i <= 4; ++i) {
		for (int j{ 1 }; j <= 6; ++j) {

			board[i][j].p_left_down = &board[i + 1][j - 1];

		}
	}

	//link p_left_ups
	for (int i{ 1 }; i <= 5; ++i) {
		for (int j{ 1 }; j <= 6; ++j) {

			board[i][j].p_left_up = &board[i - 1][j - 1];

		}
	}
	

}

void print_board(space board[6][7]) {
	
	std::cout << "_______________" << std::endl;
	std::cout << "|";
	for (int i{ 0 }; i <= 6; ++i) {
		std::cout << i;
		if (i != 6) {
			std::cout << "_";
		}
	}
	std::cout << "|" << std::endl;
	
	for (int i{ 0 }; i <= 5; ++i) {
		
		
		std::cout << "|";

		for (int j{ 0 }; j <= 6; ++j) {
			
			if (board[i][j].identity == 0) {
				std::cout << "-";
			} else if (board[i][j].identity == 1) {
				std::cout << "X";
			}
			else {
				std::cout << "O";
			}
			if (j != 6) {
				if (i != 5) {
					std::cout << " ";
				}
				else {
					std::cout << "_";
				}
				
			}
			
			
		}
		std::cout << "|" <<std::endl;
	}
	
}

bool insert(space board[6][7], int col, bool is_x, bool print) {

	bool is_valid{ false };

	if (board[0][col].identity == 0 && col >= 0 && col <= 6) { // if the input is valid
		is_valid = true;
		if (board[5][col].identity == 0) { // if the column is empty
			if (is_x) {
				board[5][col].identity = 1;
			}
			else {
				board[5][col].identity = 2;
			}
		}
		else {
			int i{ 0 };
			while (board[i + 1][col].identity == 0) {
				++i;
			}
			if (is_x) {
				board[i][col].identity = 1;
			}
			else {
				board[i][col].identity = 2;
			}
		}

	}
	if (print) {
		print_board(board);
	}
	return is_valid;



}

void undo(space board[6][7], int col) {
	int i{ 0 };
	while (board[i][col].identity == 0) {
		++i;
	}
	board[i][col].identity = 0;
}

bool is_won(space board[6][7]) {


	// check horizontal
	for (int i{ 5 }; i >= 0; --i) {
		for (int j{ 0 }; j <= 3; ++j) {
			if (board[i][j].identity != 0 && board[i][j].identity == board[i][j + 1].identity && board[i][j].identity == board[i][j + 2].identity && board[i][j].identity == board[i][j + 3].identity) {

				return true;
			}
		}
	}

	// check vertical
	for (int i{ 0 }; i <= 2; ++i) {
		for (int j{ 0 }; j <= 6; ++j) {
			if (board[i][j].identity != 0 && board[i][j].identity == board[i + 1][j].identity && board[i][j].identity == board[i + 2][j].identity && board[i][j].identity == board[i + 3][j].identity) {

				return true;
			}
		}
	}

	// check diagonal right
	for (int i{ 3 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			if (board[i][j].identity != 0 && board[i][j].identity == board[i - 1][j + 1].identity && board[i][j].identity == board[i - 2][j + 2].identity && board[i][j].identity == board[i - 3][j + 3].identity) {

				return true;
			}
		}
	}

	// check diagonal left
	for (int i{ 3 }; i <= 5; ++i) {
		for (int j{ 3 }; j <= 6; ++j) {
			if (board[i][j].identity != 0 && board[i][j].identity == board[i - 1][j - 1].identity && board[i][j].identity == board[i - 2][j - 2].identity && board[i][j].identity == board[i - 3][j - 3].identity) {

				return true;
			}
		}
	}

	return false;

} 

bool is_won(space board[6][7], int prev) { // Using this one!!!

	// find the exact location
	int i{ 0 };
	while (board[i][prev].identity == 0) {
		++i;
	}	// location is now board[i][prev]
	
	int tmp_v = i; // vertical coordinate
	int tmp_h = prev; // horizontal coordinate
	int token_counter{ 1 }; // count to four to win!
	
	// check vertical
		// Down (dont check above)
	while (board[tmp_v][prev].p_down != nullptr && board[tmp_v][prev].p_down->identity == board[i][prev].identity) { 

		++token_counter;
		++tmp_v;

	}

	if (token_counter >= 4) {
		return true;
	}
	else {
		token_counter = 1;
		tmp_v = i;
	}

	// check horizontal
		// Right
	while (board[i][tmp_h].p_right != nullptr && board[i][tmp_h].p_right->identity == board[i][prev].identity) {
		++token_counter;
		++tmp_h;
	}
	
	tmp_h = prev;

		// Left
	while (board[i][tmp_h].p_left != nullptr && board[i][tmp_h].p_left->identity == board[i][prev].identity) {
		++token_counter;
		--tmp_h;
	}

	if (token_counter >= 4) {
		return true;
	}
	else {
		token_counter = 1;
		tmp_h = prev;
	}

	// check diagonal (up-right)
		// up-right
	while (board[tmp_v][tmp_h].p_right_up != nullptr && board[tmp_v][tmp_h].p_right_up->identity == board[i][prev].identity) {
		++token_counter;
		++tmp_h;
		--tmp_v;
	}
	tmp_h = prev;
	tmp_v = i;
		// down-left
	while (board[tmp_v][tmp_h].p_left_down != nullptr && board[tmp_v][tmp_h].p_left_down->identity == board[i][prev].identity) {
		++token_counter;
		--tmp_h;
		++tmp_v;
	}

	if (token_counter >= 4) {
		return true;
	}
	else {
		token_counter = 1;
		tmp_h = prev;
		tmp_v = i;
	}

	// check diagonal (down-right)
		// Down-right
	while (board[tmp_v][tmp_h].p_right_down != nullptr && board[tmp_v][tmp_h].p_right_down->identity == board[i][prev].identity) {
		++token_counter;
		++tmp_h;
		++tmp_v;
	}
	tmp_h = prev;
	tmp_v = i;
		// Up-left
	while (board[tmp_v][tmp_h].p_left_up != nullptr && board[tmp_v][tmp_h].p_left_up->identity == board[i][prev].identity) {
		++token_counter;
		--tmp_h;
		--tmp_v;
	}

	if (token_counter >= 4) {
		return true;
	}

	return false;

}

int row_tokens(space board[6][7], int row) {
	int num_tokens{ 0 };
	for (int i{ 0 }; i <= 6; ++i) {
		if (board[row][i].identity != 0) {
			++num_tokens;
		}
	}
	return num_tokens;

}

int can_win(space board[6][7], int id) {
	
	// Horizontal
	// check the number of occupied spaces (for efficiency), if > 3, stop
	int row{ 5 };
	int num_tokens{ 0 }; // reused throughout function
	int tmp{ 0 };
	
	while (row_tokens(board, row) >= 3) {
		--row;
	}
	if (row < 5) {
		++row;
	}
	
	// check horizontal
	for (int i{ row }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i][j + k].identity == id) {
					++num_tokens;
				}
			}
			if (num_tokens == 3) {
				tmp = 0;
				while (board[i][j + tmp].identity == id) {
					++tmp;

				}
				if ((board[i][j + tmp].p_down == nullptr || board[i][j + tmp].p_down->identity != 0)/*if sapce below winning spot is occupied*/
					&& board[i][j + tmp].identity == 0 /*if winning sopt is unoccupied*/) {
					return j + tmp;
				}
			}
			num_tokens = 0;
		}
	
	} // Done
	
	tmp = 0;
	
	// Vertical
	// efficiency
	row = 5;
	while (row >= 0 && row_tokens(board, row) >= 1) {
		--row;
	}
	if (row < 5 && row != 0) {
		++row;
	}

	
	// check vertical
	if (row < 3) {
		for (int i{ row }; i <= 3; ++i) {
			for (int j{ 0 }; j <= 6; ++j) {
				for (int k{ 0 }; k <= 2; ++k) {
					if (board[i + k][j].identity == id) {
						++num_tokens;
					}

				}

				if ((num_tokens == 3 && board[i][j].p_up != nullptr) && (board[i][j].p_up->identity == 0)) {
					return j;
				}
				num_tokens = 0;

			}
		} 
	} // Done

	// check diagonal up-right
	
	for (int i{ 3 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i - k][j + k].identity == id) {
					++num_tokens;
				}
				
				
			}
			if (num_tokens == 3) {
				tmp = 0;
				while (board[i - tmp][j + tmp].identity == id) {
					++tmp;
				}
				
				if (board[i - tmp][j + tmp].identity == 0 && (board[i - tmp][j + tmp].p_down == nullptr || board[i - tmp][j + tmp].p_down->identity != 0)) {
					
					return j + tmp;
				}

			}
			num_tokens = 0;
		}
	}
	
	// check diagonal down-right

	for (int i{ 0 }; i <= 2; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i + k][j + k].identity == id) {
					++num_tokens;
				}


			}
			if (num_tokens == 3) {
				tmp = 0;
				while (board[i + tmp][j + tmp].identity == id) {
					++tmp;
				}

				if (board[i + tmp][j + tmp].identity == 0 && (board[i + tmp][j + tmp].p_down == nullptr || board[i + tmp][j + tmp].p_down->identity != 0)) {

					return j + tmp;
				}

			}
			num_tokens = 0;
		}
	}


	return 7;
}

int scenario(space board[6][7], int i, int j, int tmp, int tmp_two, int diag, int scen_id, bool using_tmp, bool O_block, bool X_win) {
	if (using_tmp) {
		if (tmp == scen_id && (board[i + diag * tmp][j + tmp].p_down == nullptr || board[i + diag * tmp][j + tmp].p_down->identity != 0)) { // if the sequence is {- - O O}
			if (!O_block && !X_win) { // if we dont want X to block our oppurtunity or let X win
				insert(board, j + tmp, false, false); /**temporary insertion, will be removed **/
				if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
					undo(board, j + tmp);
					return j + tmp;
				}
				undo(board, j + tmp);
			}
			else if (!X_win) { // if we will let X block our oppurtunity
				insert(board, j + tmp, false, false); /**temporary insertion, will be removed **/
				if (can_win(board, 1) == 7) {
					undo(board, j + tmp);
					return j + tmp;
				}
				undo(board, j + tmp);
			}
			else { // if we are forced to let X win
				return j + tmp;
			}
			
			
		}
	}
	else {
		if (tmp == scen_id && (board[i + diag * tmp_two][j + tmp_two].p_down == nullptr || board[i + diag * tmp_two][j + tmp_two].p_down->identity != 0)) { // if the sequence is {- - O O}
			if (!O_block && !X_win) {
				insert(board, j + tmp_two, false, false); /**temporary insertion, will be removed **/
				if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
					undo(board, j + tmp_two);
					return j + tmp_two;
				}
				undo(board, j + tmp_two);
			}
			else if (!X_win) {
				insert(board, j + tmp_two, false, false); /**temporary insertion, will be removed **/
				if (can_win(board, 1) == 7) {
					undo(board, j + tmp_two);
					return j + tmp_two;
				}
				undo(board, j + tmp_two);
			}
			else {
				return j + tmp_two;
			}
			// make sure that we arent opening an oppurtunity for x to win, or giving x and oppurtunity to close our chance to win
			
		}
	}
	return 7;
	
}

int triple_scenarios(space board[6][7], int tmp, int tmp_two, int i, int j, int diag, bool O_block, bool X_win) {

	if (board[i + diag*tmp][j + tmp].identity == 0 && board[i + diag*tmp_two][j + tmp_two].identity == 0) { // gotta make sure that the spaces are empty
		int tmp_three{};
		
		if (tmp + 1 == tmp_two) { // if the open spaces are next to each other
			
			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, false, O_block, X_win); // if the sequence is {- - O O} -> Place token here: {- O O O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, true, O_block, X_win); // if the sequence is {- - O O} -> Place token here: {O - O O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 1, false, O_block, X_win); // if the sequence is {O - - O} -> Place token here: {O - O O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 1, true, O_block, X_win); // if the sequence is {O - - O} -> Place token here: {O O - O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 2, true, O_block, X_win); // if the sequence is {O O - -} -> Place token here: {O O O -}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 2, false, O_block, X_win); // if the sequence is {O O - -} -> Place token here: {O O - O}
			if (tmp_three != 7) {
				return tmp_three;
			}

		}
		else if (tmp + 2 == tmp_two) { // if the open spaces are one space away from each other
			
			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, false, O_block, X_win);  // if the sequence is {- O - O} -> Place token here: {- O O O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, true, O_block, X_win); // if the sequence is {- O - O} -> Place token here: {O O - O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 1, true, O_block, X_win); // if the sequence is {O - O -} -> Place token here: {O O O -}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 1, false, O_block, X_win); // if the sequence is {O - O -} -> Place token here: {O - O O}
			if (tmp_three != 7) {
				return tmp_three;
			}
		}
		else {  //if the open spaces are two away from each other
			
			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, false, O_block, X_win);  // if the sequence is {- O O -} -> Place token here: {- O O O}
			if (tmp_three != 7) {
				return tmp_three;
			}

			tmp_three = scenario(board, i, j, tmp, tmp_two, diag, 0, true, O_block, X_win); // if the sequence is {- O O -} -> Place token here: {O O O -}
			if (tmp_three != 7) {
				return tmp_three;
			}
		}

	}
	return 7;

}

int three_in_sequence(space board[6][7], int id, bool O_block, bool X_win) {


	// Horizontal
	// check the number of occupied spaces (for efficiency), if > 2, stop
	int row{ 5 };
	int num_tokens{ 0 }; // reused throughout function
	int tmp{ 0 };
	int tmp_two{ 0 };
	int scen = 0;

	while (row_tokens(board, row) >= 2) {
		--row;
	}
	if (row < 5) {
		++row;
	}

	// check horizontal
	for (int i{ row }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i][j + k].identity == id) {
					++num_tokens;
				}
			}
			if (num_tokens == 2) {
				
				
				tmp = 0;
				tmp_two = 1;
				while (board[i][j + tmp].identity == id) { // first unoccupied space
					++tmp;

				}
				while (board[i][j + tmp + tmp_two].identity == id) { // second unoccupied space
					++tmp_two;

				}
				tmp_two += tmp;

				// case scenarios
				scen = triple_scenarios(board, tmp, tmp_two, i, j, 0, O_block, X_win);
				if (scen != 7) {
					return scen;
				}


			}
			num_tokens = 0;
		}

	} // Done

	tmp = 0;


   // check diagonal up-right

	for (int i{ 3 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i - k][j + k].identity == id) {
					++num_tokens;
				}


			}
			if (num_tokens == 2) {
				// CODE HERE
				
				tmp = 0;
				tmp_two = 1;
				while (board[i - tmp][j + tmp].identity == id) { // first unoccupied space
					++tmp;

				}
				while (board[i - tmp - tmp_two][j + tmp + tmp_two].identity == id) { // second unoccupied space
					++tmp_two;

				}
				tmp_two += tmp;
				
				// case scenarios
				scen = triple_scenarios(board, tmp, tmp_two, i, j, -1, O_block, X_win);
				if (scen != 7) {
					return scen;
				}
				
			}
			num_tokens = 0;
		}
	}

	// check diagonal down-right
	
	for (int i{ 0 }; i <= 2; ++i) {
		for (int j{ 0 }; j <= 3; ++j) {
			for (int k{ 0 }; k <= 3; ++k) {
				if (board[i + k][j + k].identity == id) {
					++num_tokens;
				}
				
			}
			
			if (num_tokens == 2) {

				tmp = 0;
				tmp_two = 1;
				while (board[i + tmp][j + tmp].identity == id) { // first unoccupied space
					++tmp;
				}
				while (board[i + tmp + tmp_two][j + tmp + tmp_two].identity == id) { // second unoccupied space
					++tmp_two;
				}
				tmp_two += tmp;
				
				
				// case scenarios
				scen = triple_scenarios(board, tmp, tmp_two, i, j, 1, O_block, X_win);
				if (scen != 7) {
					return scen;
				}
				
			}
			num_tokens = 0;
		}
	}

	// Vertical
	// efficiency
	row = 5;
	while (row_tokens(board, row) >= 1 && row >= 0) {
		--row;
	}
	if (row < 5 && row != 0) {
		++row;
	}
	
	if (row < 5) {
		
		// check vertical
		for (int i{ row }; i <= 4; ++i) { 
			for (int j{ 0 }; j <= 6; ++j) {
				for (int k{ 0 }; k < 2; ++k) {
					if (board[i + k][j].identity == id) {
						++num_tokens;
					}
				}
				if ((num_tokens == 2 && board[i][j].p_up != nullptr) && (board[i][j].p_up->identity == 0) && board[i][j].p_up->p_up != nullptr) {
					if (!O_block && !X_win) {
						
						insert(board, j, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j);
							return j;
						}
						undo(board, j);
					}
					else if (!X_win) {
						insert(board, j, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j);
							return j;
						}
						undo(board, j);
					}
					else {
						return j;
					}
				}
				num_tokens = 0;
			}
		}

	}
	return 7;
}

int two_in_sequence(space board[6][7], int id, bool O_block, bool X_win) {

	for (int i{ 0 }; i <= 5; ++i) {
		for (int j{ 0 }; j <= 6; ++j) {
		
			if (board[i][j].identity == id) {

				if (board[i][j].p_right_up != nullptr && board[i][j].p_right_up->identity == 0 && board[i][j].p_right->identity != 0) { // place token diagonally right up
					if (!O_block && !X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else if (!X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else {
						return j + 1;
					}
					
				}
				if (board[i][j].p_left_up != nullptr && board[i][j].p_left_up->identity == 0 && board[i][j].p_left->identity != 0) { // place token diagonally left up
					if (!O_block && !X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else if (!X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else {
						return j - 1;
					}
				}
				if (board[i][j].p_right != nullptr && board[i][j].p_right->identity == 0 && (board[i][j].p_right_down == nullptr || board[i][j].p_right_down->identity != 0)) { // place token directly right
					if (!O_block && !X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else if (!X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else {
						return j + 1;
					}
				}
				if (board[i][j].p_left != nullptr && board[i][j].p_left->identity == 0 && (board[i][j].p_left_down == nullptr || board[i][j].p_left_down->identity != 0)) { // place token directly left
					if (!O_block && !X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else if (!X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else {
						return j - 1;
					}
				}
				if (board[i][j].p_right_down != nullptr && board[i][j].p_right_down->identity == 0 && (board[i][j].p_right_down->p_down == nullptr || board[i][j].p_right_down->p_down->identity != 0)) { // place token diagonally right down
					if (!O_block && !X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else if (!X_win) {
						insert(board, j + 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j + 1);
							return j + 1;
						}
						undo(board, j + 1);
					}
					else {
						return j + 1;
					}
				}
				if (board[i][j].p_left_down != nullptr && board[i][j].p_left_down->identity == 0 && (board[i][j].p_left_down->p_down == nullptr || board[i][j].p_left_down->p_down->identity != 0)) { // place token diagonally right down
					if (!O_block && !X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else if (!X_win) {
						insert(board, j - 1, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j - 1);
							return j - 1;
						}
						undo(board, j - 1);
					}
					else {
						return j - 1;
					}
				}
				if (board[i][j].p_up != nullptr && board[i][j].p_up->identity == 0) { // place token on top
					if (!O_block && !X_win) {
						insert(board, j, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7 && can_win(board, 2) == 7) {
							undo(board, j);
							return j;
						}
						undo(board, j);
					}
					else if (!X_win) {
						insert(board, j, false, false); /**temporary insertion, will be removed **/
						if (can_win(board, 1) == 7) {
							undo(board, j);
							return j;
						}
						undo(board, j);
					}
					else {
						return j;
					}
				}

			}

		}
	}
	return 7;

}

int computer_move(space board[6][7]) {
	int tmp{ 0 };
	
	// see if I can win
	tmp = can_win(board, 2);
	std::cout << "one: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}

	// stop X from winning
	
	tmp = can_win(board, 1);
	std::cout << "two: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	
	// get three in sequence to create an oppurtunity (with space in middle (or on edge)) -> without opening oppurtunities for X to win or for O to be blocked

	tmp = three_in_sequence(board, 2, false, false);
	std::cout << "three: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}

	// stop X from getting three in sequence -> without opening oppurtunities for X to win or for O to be blocked

	tmp = three_in_sequence(board, 1, false, false);
	std::cout << "four: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}



	// get two in a row -> without opening oppurtunities for X to win or for O to be blocked

	tmp = two_in_sequence(board, 2, false, false);
	std::cout << "five: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}

	// just play next to X -> without opening oppurtunities for X to win or for O to be blocked
	tmp = two_in_sequence(board, 1, false, false);
	std::cout << "six: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}

	// LET OUR (WINNING) SPOT BE BLOCKED BECAUSE THERE ARE NO OTHER MOVES 

	// Get three in a row
	tmp = three_in_sequence(board, 2, true, false);
	std::cout << "seven: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// Stop X from getting three in a row
	tmp = three_in_sequence(board, 1, true, false);
	std::cout << "eight: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// get two in a row
	tmp = two_in_sequence(board, 2, true, false);
	std::cout << "nine: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// Stop X from getting two in a row
	tmp = two_in_sequence(board, 1, true, false);
	std::cout << "ten: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	
	// WORST CASE SCENARIOS -> if we cant do anything else, we are forced to make a move that allows X to win
	
	// Get three in a row
	tmp = three_in_sequence(board, 2, true, true);
	std::cout << "eleven: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// Stop X from getting three in a row
	tmp = three_in_sequence(board, 1, true, true);
	std::cout << "twelve: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// get two in a row
	tmp = two_in_sequence(board, 2, true, true);
	std::cout << "thirteen: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	// Stop X from getting two in a row
	tmp = two_in_sequence(board, 1, true, true);
	std::cout << "fourteen: " << tmp << std::endl;
	if (tmp != 7) {
		return tmp;
	}
	std::cout << "Error: Move not found, returning zero" << std::endl;

	return 0;
}

void two_player_game() {
	space board[6][7]{ 0 };
	create_board(board);
	int input{ 0 };
	print_board(board);
	while (true) {
		do {
			std::cout << "X: ";
			std::cin >> input;
		} while (!insert(board, input, true, true));

		if (is_won(board, input)) {
			std::cout << "X Wins!\n";
			break;
		}

		do {
			std::cout << "O: ";
			std::cin >> input;

		} while (!insert(board, input, false, true));

		if (is_won(board, input)) {
			std::cout << "O wins!\n";
			break;
		}
	}




}

void one_player_game() {

	space board[6][7];
	create_board(board);
	int input{ 0 };
	print_board(board);
	while (true) {
		do {
			std::cout << "X: ";
			std::cin >> input;
		} while (!insert(board, input, true, true));

		if (is_won(board, input)) {
			std::cout << "X Wins!\n";
			break;
		}
		
		insert(board, computer_move(board), false, true);
		

		if (is_won(board)) {
			std::cout << "O wins!\n";
			break;
		}
	}



}


int main()
{
	std::string input{ "" };
	bool valid_input{ false };
	do {
		std::cout << "Enter \"one\" for a one player game, or enter \"two\" for a two player game\n";
		std::cin >> input;
		if (input == "one") {
			one_player_game();
			valid_input = true;
		}
		else if (input == "two") {
			two_player_game();
			valid_input = true;
		}
		
	} while (!valid_input);
	
	return 0;
}
