#ifndef GENERATE_MOVES_H
#define GENERATE_MOVES_H

#include "board.h"
#include <list>

// Implemented TODO remove this comment
#define BSHIFT_INI_POS 0  // 6b
#define BSHIFT_FINAL_POS 6  // 6b
#define BSHIFT_COLOR 12  // 1b
#define BSHIFT_PIECE_TYPE 13 // 3b
#define BSHIFT_IS_CAPTURE 16 // 1b
#define BSHIFT_TYPE_PROMOTION 17 // 3b

#define BMASK_FINAL_POS 0b00000000000000000000111111000000
#define BMASK_PIECE_TYPE 0b00000000000000001110000000000000
#define BMASK_COLOR 0b00000000000000000001000000000000
#define BMASK_IS_CAPTURE 0b00000000000000010000000000000000
#define BMASK_TYPE_PROMOTION 0b00000000000011100000000000000000

// NOT Implemented TODO remove this comment
#define BSHIFT_IS_ENPASSANT 19 // 1b

typedef int s_int;

void generate_moves(std::list<s_int> * l, class Board * board, int color);
// TODO add capture_flag in the end 
// TODO add pawn promotions
s_int generate_move_int(int piece_type, int color, int position_ini, int position_final, bool is_capture, int type_promotion = 0, int castling = 0, int en_pessant = 0);


// TODO PAWN MOVES
void generate_pawn_moves_white(std::list<s_int> * l, int i, class Board*  board);
void generate_pawn_moves_black(std::list<s_int> * l, int i, class Board*  board);
void generate_pawn_promotions(std::list<s_int> * l, int ini_pos, int fin_pos, class Board*  board, int color, bool is_capture);

void generate_rook_moves(std::list<s_int>* l, int i, class Board* board, int color, int piece_type);
void generate_bishop_moves(std::list<s_int>* l, int i, class Board* board, int color, int piece_type);
void generate_king_moves(std::list<s_int>* l, int i, class Board* board, int color);
void generate_knight_moves(std::list<s_int>* l, int i, Board* board, int color);

void check_and_append_move(std::list<s_int>* l, int ini_pos, int fin_pos, Board* board, int color, bool is_capture, int type_check, int type_promotion);
void print_moves(std::list<s_int> const * l);

#endif // !GENERATE_MOVES_H
