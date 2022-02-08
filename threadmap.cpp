
#include "threadmap.h"

#include <iostream> // to debug only

void generate_threadmap(class Board* board, int color, int* threadmap) {
	int aux_color = (color == WHITE) ? BLACK : WHITE;

	for (int i = 0; i < 64; i++) {
		if (board->Color[i] == aux_color) {
			int rank = i / 8;

			switch (board->Piece[i]) {
			case PAWN:
				if (aux_color == WHITE) {
					threadmap_pawn_black(threadmap, i, rank, board);
				}
				else {
					threadmap_pawn_white(threadmap, i, rank, board);
				}
				
				break;
			case KNIGHT:
				threadmap_knight(threadmap, i, rank, board, color);
				break;

			case BISHOP:
				threadmap_bishop(threadmap, i, board, color);
				break;

			case ROOK:
				threadmap_rook(threadmap, i, rank, board, color);
				break;

			case QUEEN:
				threadmap_queen(threadmap, i, rank, board, color);
				break;

			case KING:
				threadmap_king(threadmap, i, rank, board, color);
				break;

			default:break;
			}
		}
	}

}


void threadmap_pawn_black(int* threadmap, int i, int rank, class Board* board) {
	if (rank != 7) {
		if ((i % 8 == 0) && (board->Color[i+9] == EMPTY)) {
			threadmap[i + 9] = 1;
		}
		else if ((i % 8 == 7) && ((board->Color[i + 7] == EMPTY))) {
			threadmap[i + 7] = 1;
		}
		else {
			if (board->Color[i + 9] == EMPTY) {
				threadmap[i + 9] = 1;
			}
			if (board->Color[i + 7] == EMPTY) {
				threadmap[i + 7] = 1;
			}
		}
	}
}

void threadmap_pawn_white(int* threadmap, int i, int rank, class Board* board) {
	if (rank != 0) {
		if ((i % 8 == 0) && (board->Color[i - 7] == EMPTY)) {
			threadmap[i - 7] = 1;
		}
		else if ((i % 8 == 7) && ((board->Color[i - 9] == EMPTY))) {
			threadmap[i - 9] = 1;
		}
		else {
			if (board->Color[i - 9] == EMPTY) {
				threadmap[i - 9] = 1;
			}
			if (board->Color[i - 7] == EMPTY) {
				threadmap[i - 7] = 1;
			}
		}
	}
}

void threadmap_knight(int* threadmap, int i, int rank, class Board* board, int color) {
	int knight_pos = i + 15;
	if ((((knight_pos) / 8 - rank == 2) && (knight_pos < 64)) && ((board->Color[knight_pos] == EMPTY)|| ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i + 17;
	if ((((knight_pos) / 8 - rank == 2) && (knight_pos < 64)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i + 10;
	if ((((knight_pos) / 8 - rank == 1) && (knight_pos < 64)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i + 6;
	if ((((knight_pos) / 8 - rank == 1) && (knight_pos < 64)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i - 10;
	if ((((knight_pos) / 8 - rank == -1) && (knight_pos > 0)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i - 6;
	if ((((knight_pos) / 8 - rank == -1) && (knight_pos > 0)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i - 15;
	if ((((knight_pos) / 8 - rank == -2) && (knight_pos > 0)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
	knight_pos = i - 17;
	if ((((knight_pos) / 8 - rank == -2) && (knight_pos > 0)) && ((board->Color[knight_pos] == EMPTY) || ((board->Piece[knight_pos] == KING) && (board->Color[knight_pos] == color)))) {
		threadmap[knight_pos] = 1;
	}
}

void threadmap_rook(int* threadmap, int i, int rank, class Board* board, int color) {
	int aux = i + 8;
	while ((aux < 64) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		aux += 8;
	}

	aux = i - 8;
	while ((aux >= 0) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		aux -= 8;
	}

	aux = i + 1;
	while ((rank == aux / 8) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		aux += 1;
	}
	
	aux = i - 1;
	while (((rank == aux / 8) && (aux >= 0)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		aux -= 1;
	}
}

void threadmap_bishop(int* threadmap, int i, class Board* board, int color) {
	int aux = i + 9;
	int rank = i / 8;
	

	while (((aux < 64) && (rank == (aux/8) - 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		rank = aux / 8;
		aux += 9;
	}
	aux = i + 7;
	rank = i / 8;
	while (((aux < 64) && (rank == (aux / 8) - 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		
		threadmap[aux] = 1;
		rank = aux / 8;
		aux += 7;
	}

	aux = i - 9;
	rank = i / 8;
	while (((aux >= 0) && (rank == (aux / 8) + 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		rank = aux / 8;
		aux -= 9;
	}
	aux = i - 7;
	rank = i / 8;
	while (((aux >= 0) && (rank == (aux / 8) + 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
		rank = aux / 8;
		aux -= 7;
	}
}

void threadmap_queen(int* threadmap, int i, int rank, class Board* board, int color) {
	threadmap_rook(threadmap, i, rank, board, color);
	threadmap_bishop(threadmap, i, board, color);
}

void threadmap_king(int* threadmap, int i, int rank, class Board* board, int color) {
	int aux = i + 1;
	if ((aux / 8 == rank) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i - 1;
	if (((aux / 8 == rank) && (aux >= 0)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i + 8;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i + 7;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i + 9;
	if (((aux < 64) && (rank == (aux / 8) - 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i - 8;
	if (((aux >= 0) && (rank == (aux/8) + 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i - 7;
	if (((aux >= 0) && (rank == (aux / 8) + 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
	aux = i - 9;
	if (((aux >= 0) && (rank == (aux / 8) + 1)) && ((board->Color[aux] == EMPTY) || ((board->Piece[aux] == KING) && (board->Color[aux] == color)))) {
		threadmap[aux] = 1;
	}
}

int* clean_threadmap(int* threadmap) {
	for (int i = 0; i < 64; i++) {
		threadmap[i] = 0;
	}
	return threadmap;
}