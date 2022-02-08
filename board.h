#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "bitboard.h"
#include "piecedef.h"

class Board {
private:
	// For the function change piece so it remembers what it was
	int colorSwaping = 0;
	int pieceSwaping = 0;
public:
	int WhiteKingPosition; // TODO INITIALIZE BOTH AND SOME SAFETY IN CASE THERE ARE NO KINGS ??
	int BlackKingPosition;
	int threadmap[64];
	int Color[64] = {
		BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
		BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
	};
	int Piece[64] = {
		ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
		PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
		PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
		ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK
	};
	
	Board();  // Declare constructor
	~Board();           //  and destructor.
	void print();
	int parse_line(std::string str);
	void change_piece_position(int type, int color, int p_ini, int p_fin);
	void return_piece_position(int type, int color, int p_fin, int p_ini);
	bool is_king_NOT_in_check(int color);
	int parse_fen_description(std::string fen_str);
	void reset(int type); 
};


#endif