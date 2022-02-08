
#include <iostream>
#include <string> 
#include <list>

#include "board.h"
#include "threadmap.h"

#include "printing.h"
#include "generatemoves.h"

#include "threadmap.h" // DEBUG TO SEE WHO MOVES. TODO remove

using namespace std;

int main() {

	Board chess_board;
	std::list<s_int> move_list;
	
	string str;

	chess_board.reset(0);

	while (str != "x") {
		if (str == "0") {
			chess_board.reset(0);
		}
		getline(cin, str);
		
		if (chess_board.parse_line(str) != 0) {
			chess_board.print();

			cout << endl;
			cout << "Threadmap White:" << endl;
			generate_threadmap(&chess_board, WHITE, chess_board.threadmap);
			print_array(chess_board.threadmap);
			clean_threadmap(chess_board.threadmap);

			cout << endl;
			cout << "Threadmap Black" << endl;
			generate_threadmap(&chess_board, BLACK, chess_board.threadmap);
			print_array(chess_board.threadmap);
			clean_threadmap(chess_board.threadmap);
			

			
			cout << endl;
			//cout << "Moves for White" << endl;
			generate_moves(&move_list, &chess_board, WHITE);
			print_moves(&move_list);
			move_list.clear();
			
		}
	}

	/*
	int to_move;
	getline(cin, str);
	to_move = chess_board.parse_fen_description(str);
	chess_board.print();
	if (to_move == WHITE) {
		cout << "White to move" << endl;
	}
	else if (to_move == BLACK) {
		cout << "Black to move" << endl;
	}
	generate_moves(&move_list, &chess_board, WHITE);
	print_moves(&move_list);
	
	system("pause");
	*/
	return EXIT_SUCCESS;
}