#include "generatemoves.h"
#include "threadmap.h"
#include <iostream>


void generate_moves(std::list<s_int>* l, class Board * board, int color) {
	for (int i = 0; i < 64; i++) {
		if (board->Color[i] == color) {
			switch (board->Piece[i]) {
			case PAWN:
				if (color == WHITE) {
					generate_pawn_moves_white(l, i, board);
				}
				else {
					generate_pawn_moves_black(l, i, board);
				}
				break;
			case ROOK:
				generate_rook_moves(l, i, board, color, ROOK);
				break;
			case BISHOP:
				generate_bishop_moves(l, i, board, color, BISHOP);
				break;
			case QUEEN: 
				generate_bishop_moves(l, i, board, color, QUEEN);
				generate_rook_moves(l, i, board, color, QUEEN);
				break;
			case KNIGHT: 
				generate_knight_moves(l, i, board, color);
				break;
			case KING:
				generate_king_moves(l, i, board, color);
				break;
			default:break;
			}
		}
	}
}

void generate_rook_moves(std::list<s_int>* l, int i, Board* board, int color, int piece_type) {
	int aux = i + 8;
	int rank = i / 8;
	bool capture_flag = 0;

	while ((aux < 64) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		// Move rook to new position
		board->change_piece_position(piece_type, color, i, aux);
		// Check the king is not in check
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		// Leave the board as it was
		board->return_piece_position(piece_type, color, aux, i);
		aux += 8;
	}

	aux = i - 8;
	capture_flag = 0;
	while ((aux >= 0) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);
		aux -= 8;
	}

	aux = i + 1;
	capture_flag = 0;
	while ((rank == aux / 8) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);
		aux += 1;
	}

	aux = i - 1;
	capture_flag = 0;
	while ((rank == aux / 8) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);
		aux -= 1;
	}
}

void generate_bishop_moves(std::list<s_int>* l, int i, Board* board, int color, int piece_type) {
	int aux = i + 9;
	int rank = i / 8;
	bool capture_flag = 0;

	while (((aux < 64) && (rank == (aux / 8) - 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);
		rank = aux / 8;
		aux += 9;
	}
	aux = i + 7;
	rank = i / 8;
	capture_flag = 0;
	while (((aux < 64) && (rank == (aux / 8) - 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);

		rank = aux / 8;
		aux += 7;
	}
	aux = i - 9;
	rank = i / 8;
	capture_flag = 0;
	while (((aux >= 0) && (rank == (aux / 8) + 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);

		rank = aux / 8;
		aux -= 9;
	}
	aux = i - 7;
	rank = i / 8;
	capture_flag = 0;
	while (((aux >= 0) && (rank == (aux / 8) + 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(piece_type, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(piece_type, color, i, aux, capture_flag));
		}
		board->return_piece_position(piece_type, color, aux, i);

		rank = aux / 8;
		aux -= 7;
	}
}

void generate_knight_moves(std::list<s_int>* l, int i, Board* board, int color) {
	int rank = i / 8;
	
	int knight_pos = i + 15;
	bool capture_flag = 0;

	if ((((knight_pos) / 8 - rank == 2) && (knight_pos < 64)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i + 17;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == 2) && (knight_pos < 64)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i + 10;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == 1) && (knight_pos < 64)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i + 6;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == 1) && (knight_pos < 64)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i - 10;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == -1) && (knight_pos > 0)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i - 6;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == -1) && (knight_pos > 0)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i - 15;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == -2) && (knight_pos > 0)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
	knight_pos = i - 17;
	capture_flag = 0;
	if ((((knight_pos) / 8 - rank == -2) && (knight_pos > 0)) && (board->Color[knight_pos] != color) && (!capture_flag)) {
		if (board->Color[knight_pos] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KNIGHT, color, i, knight_pos);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KNIGHT, color, i, knight_pos, capture_flag));
		}
		board->return_piece_position(KNIGHT, color, knight_pos, i);
	}
}

// TODO apply masks to color/piece_type/etc as a measure in case they overflow ex color = 2 breaks the encoding sys
// TODO Also, check captures 
s_int generate_move_int(int piece_type, int color, int position_ini, int position_final, bool is_capture, int type_promotion, int castling, int en_pessant) {
	s_int encoded_move;
	encoded_move = position_ini;
	encoded_move = encoded_move | (position_final << BSHIFT_FINAL_POS);
	encoded_move = encoded_move | (color << BSHIFT_COLOR);
	encoded_move = encoded_move | (piece_type << BSHIFT_PIECE_TYPE);
	encoded_move = encoded_move | (is_capture << BSHIFT_IS_CAPTURE);
	encoded_move = encoded_move | (type_promotion << BSHIFT_TYPE_PROMOTION);
	return encoded_move;
}

// TODO finish king moves
// TODO CASTILING
void generate_king_moves(std::list<s_int>* l, int i, Board* board, int color) {
	int aux = i + 1;
	int rank = i / 8;
	bool capture_flag = 0;

	if ((aux / 8 == rank) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i - 1;
	capture_flag = 0;
	if (((aux / 8 == rank) && (aux >= 0)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i + 8;
	capture_flag = 0;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i + 7;
	capture_flag = 0;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i + 9;
	capture_flag = 0;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i - 8;
	capture_flag = 0;
	if (((aux >= 0) && (rank == (aux / 8) + 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i - 7;
	capture_flag = 0;
	if (((aux >= 0) && (rank == (aux / 8) + 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
	aux = i - 9;
	capture_flag = 0;
	if (((aux >= 0) && (rank == (aux / 8) + 1)) && (board->Color[aux] != color) && (!capture_flag)) {
		if (board->Color[aux] != EMPTY) {
			capture_flag = 1;
		}
		board->change_piece_position(KING, color, i, aux);
		if (board->is_king_NOT_in_check(color)) {
			l->push_front(generate_move_int(KING, color, i, aux, capture_flag));
		}
		board->return_piece_position(KING, color, aux, i);
	}
}

// TODO do the pawns promotion
void generate_pawn_moves_white(std::list<s_int>* l, int i, Board* board) {
	// Forward movement
	if ((i + 8 < 64) && (board->Piece[i + 8] == EMPTY)) {
		if (i / 8 == 6) {
			generate_pawn_promotions(l, i, i + 8, board, WHITE, NO_CAPTURE);
		} else{
			check_and_append_move(l, i, i+8, board, WHITE, NO_CAPTURE, PAWN, PAWN);
			/* TODO remove this comment
			board->change_piece_position(PAWN, WHITE, i, i + 8);
			if (board->is_king_NOT_in_check(WHITE)) {
				l->push_front(generate_move_int(PAWN, WHITE, i, i + 8, NO_CAPTURE));
			}
			board->return_piece_position(PAWN, WHITE, i + 8, i);
			*/
		}	
	}
	// Special first move for pawns
	if ((i / 8 == 1) && (board->Piece[i + 8] == EMPTY) && (board->Piece[i + 16] == EMPTY)) {
		board->change_piece_position(PAWN, WHITE, i, i + 16);
		if (board->is_king_NOT_in_check(WHITE)) {
			l->push_front(generate_move_int(PAWN, WHITE, i, i + 16, NO_CAPTURE));
		}
		board->return_piece_position(PAWN, WHITE, i + 16, i);
	}

	// Captures (Pawns on the side and center differenced in if)	
	if (i / 8 != 7) {
		if ((i % 8 == 7) && (board->Color[i + 9] == BLACK)) {
			if (i / 8 == 6) {
				generate_pawn_promotions(l, i, i + 9, board, WHITE, CAPTURE);
			}
			else {
				board->change_piece_position(PAWN, WHITE, i, i + 9);
				if (board->is_king_NOT_in_check(WHITE)) {
					l->push_front(generate_move_int(PAWN, WHITE, i, i + 9, CAPTURE));
				}
				board->return_piece_position(PAWN, WHITE, i + 9, i);
			}
		}
		else if ((i % 8 == 0) && (board->Color[i + 7] == BLACK)) {
			if (i / 8 == 6) {
				generate_pawn_promotions(l, i, i + 7, board, WHITE, CAPTURE);
			}
			else {
			board->change_piece_position(PAWN, WHITE, i, i + 7);
			if (board->is_king_NOT_in_check(WHITE)) {
				l->push_front(generate_move_int(PAWN, WHITE, i, i + 7, CAPTURE));
			}
			board->return_piece_position(PAWN, WHITE, i + 7, i);
			}
		}
		else {
		if (board->Color[i + 7] == BLACK) {
			if (i / 8 == 6) {
				generate_pawn_promotions(l, i, i + 7, board, WHITE, CAPTURE);
			}
			else {
				board->change_piece_position(PAWN, WHITE, i, i + 7);
				if (board->is_king_NOT_in_check(WHITE)) {
					l->push_front(generate_move_int(PAWN, WHITE, i, i + 7, CAPTURE));
				}
				board->return_piece_position(PAWN, WHITE, i + 7, i);
			}
		}
		if (board->Color[i + 9] == BLACK) {
			if (i / 8 == 6) {
				generate_pawn_promotions(l, i, i + 9, board, WHITE, CAPTURE);
			}
			else {
				board->change_piece_position(PAWN, WHITE, i, i + 9);
				if (board->is_king_NOT_in_check(WHITE)) {
					l->push_front(generate_move_int(PAWN, WHITE, i, i + 9, CAPTURE));
				}
				board->return_piece_position(PAWN, WHITE, i + 9, i);
			}
		}
		}
	}
	// Promotions
	if ((i / 8 == 7) & (board->Color[i + 8] == EMPTY)) {
		generate_pawn_promotions(l, i, i + 8, board, WHITE, NO_CAPTURE);
	}
}

void generate_pawn_promotions(std::list<s_int> * l, int ini_pos, int fin_pos, class Board*  board, int color, bool is_capture) {

	check_and_append_move(l, ini_pos, fin_pos, board, color, is_capture, PAWN, KNIGHT);
	check_and_append_move(l, ini_pos, fin_pos, board, color, is_capture, PAWN, ROOK);
	check_and_append_move(l, ini_pos, fin_pos, board, color, is_capture, PAWN, BISHOP);
	check_and_append_move(l, ini_pos, fin_pos, board, color, is_capture, PAWN, QUEEN);

	/* TODO remove this code if the ladder works
	board->change_piece_position(QUEEN, color, ini_pos, fin_pos);
	if (board->is_king_NOT_in_check(color)) {
		l->push_front(generate_move_int(PAWN, color, ini_pos, fin_pos, is_capture, QUEEN));
	}
	board->return_piece_position(PAWN, color, fin_pos, ini_pos);

	board->change_piece_position(ROOK, color, ini_pos, fin_pos);
	if (board->is_king_NOT_in_check(color)) {
		l->push_front(generate_move_int(PAWN, color, ini_pos, fin_pos, is_capture, ROOK));
	}
	board->return_piece_position(PAWN, color, fin_pos, ini_pos);

	board->change_piece_position(BISHOP, color, ini_pos, fin_pos);
	if (board->is_king_NOT_in_check(color)) {
		l->push_front(generate_move_int(PAWN, color, ini_pos, fin_pos, is_capture, BISHOP));
	}
	board->return_piece_position(PAWN, color, fin_pos, ini_pos);

	board->change_piece_position(KNIGHT, color, ini_pos, fin_pos);
	if (board->is_king_NOT_in_check(color)) {
		l->push_front(generate_move_int(PAWN, color, ini_pos, fin_pos, is_capture, KNIGHT));
	}
	board->return_piece_position(PAWN, color, fin_pos, ini_pos);
	*/
}

void generate_pawn_moves_black(std::list<s_int>* l, int i, Board* board) {

}

void print_moves(std::list<s_int> const * l) {
	// Only works on C11 if not should use iterators
	for (auto const &i : *l) {
		// To see binary 
		/*
		for (int k = 31; k >= 0; k--) {
			std::cout << ((i & (1 << k)) >> k);
		}
		*/

		// To see readable moves
		
		switch ((i & BMASK_PIECE_TYPE) >> BSHIFT_PIECE_TYPE) {
		case KING: std::cout << "King to "; break;
		case QUEEN: std::cout << "Queen to "; break;
		case BISHOP: std::cout << "Bishop to "; break;
		case ROOK: std::cout << "Rook to "; break;
		case KNIGHT: std::cout << "Knight to "; break;
		case PAWN: std::cout << "Pawn to "; break;
		default:break;
		}
		std::cout << ((i & BMASK_FINAL_POS) >> BSHIFT_FINAL_POS) << ". ";
		if ((i & BMASK_IS_CAPTURE) >> BSHIFT_IS_CAPTURE) {
			std::cout << "Capture. ";
		}
		/*
		std::cout << std::endl;
		std::cout << "Is capture: " << std::endl;
		std::cout << ((i & BMASK_IS_CAPTURE) >> BSHIFT_IS_CAPTURE) << std::endl;
		
		std::cout << "Pawn promotion type: " << std::endl;
		std::cout << ((i & BMASK_TYPE_PROMOTION) >> BSHIFT_TYPE_PROMOTION) << std::endl;
		*/
		if ((i & BMASK_TYPE_PROMOTION) >> BSHIFT_TYPE_PROMOTION) {
			std::cout << "Pawn promotes to  ";
			switch ((i & BMASK_TYPE_PROMOTION) >> BSHIFT_TYPE_PROMOTION) {
			case QUEEN: std::cout << "Queen"; break;
			case BISHOP: std::cout << "Bishop"; break;
			case ROOK: std::cout << "Rook"; break;
			case KNIGHT: std::cout << "Knight"; break;
			//case PAWN: std::cout << "Pawn"; break;
			//case KING: std::cout << "King"; break;
			default:break;
			}

		}

		std::cout << std::endl;

	}
	std::cout << "Total legal moves : " << l->size() << std::endl;
}

void check_and_append_move(std::list<s_int>* l, int ini_pos, int fin_pos, Board* board, int color, bool is_capture, int type_check, int type_promotion) {
	board->change_piece_position(type_promotion, color, ini_pos, fin_pos);
	if (board->is_king_NOT_in_check(color)) {
		l->push_front(generate_move_int(type_check, color, ini_pos, fin_pos, is_capture, type_promotion));
	}
	board->return_piece_position(type_check, color, fin_pos, ini_pos);
}