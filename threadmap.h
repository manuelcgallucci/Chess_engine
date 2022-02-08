#ifndef THREADMAP_H
#define THREADMAP_H

#include "piecedef.h"
#include "board.h"

void generate_threadmap(class Board* board, int color, int* threadmap);
int* clean_threadmap(int* threadmap);


// TODO CHAGE TO &Board instead of Board to pass by reference
void threadmap_pawn_black(int* threadmap, int i, int rank, class Board* board);
void threadmap_pawn_white(int* threadmap, int i, int rank, class Board* board);
void threadmap_rook(int* threadmap, int i, int rank, class Board* board, int color);
void threadmap_bishop(int* threadmap, int i, class Board* board, int color);
void threadmap_knight(int* threadmap, int i, int rank, class Board* board, int color);
void threadmap_queen(int* threadmap, int i, int rank, class Board* board, int color);
void threadmap_king(int* threadmap, int i, int rank, class Board*board, int color);



#endif // !THREADMAP_H
