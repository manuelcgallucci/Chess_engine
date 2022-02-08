
#include "piecedef.h"
#include "board.h"
#include "threadmap.h"
#include <string>

Board::Board() {
	//std::cout << "Contructor called" << std::endl;
}

Board::~Board() {
	//std::cout << "Destructor called" << std::endl;
}

void Board::print() {
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) {
			std::cout << std::endl;
		}
		if (Color[i] == WHITE) {
			switch (Piece[i]) {
			case PAWN: std::cout << "P"; break;
			case ROOK: std::cout << "R"; break;
			case KNIGHT: std::cout << "N"; break;
			case KING: std::cout << "K"; break;
			case QUEEN: std::cout << "Q"; break;
			case BISHOP: std::cout << "B"; break;
			default: break;
			}
		}
		else if (Color[i] == BLACK) {
			switch (Piece[i]) {
			case PAWN: std::cout << "p"; break;
			case ROOK: std::cout << "r"; break;
			case KNIGHT: std::cout << "n"; break;
			case KING: std::cout << "k"; break;
			case QUEEN: std::cout << "q"; break;
			case BISHOP: std::cout << "b"; break;
			default: break;
			}
		}
		else {
			if (BBOARD_DARK_SQUARE_MASK & (1 << i)) {
				std::cout << " "; // White space
			}
			else {
				std::cout << "@"; // Black space
			}
		}
	}
	std::cout << std::endl;
}

int Board::parse_line(std::string str) {
	if (str.length() != 4) {
		return 0;
	}

	char char_aux = str[0];
	str.erase(0, 1);

	char char_color_aux = str[0];
	str.erase(0, 1);

	int i = stoi((str));


	if ((i >= 0) && (i < 64)) {
		switch (char_aux) {
		case 'p':
			this->Piece[i] = PAWN;
			break;
		case 'r':
			this->Piece[i] = ROOK;
			break;
		case 'b':
			this->Piece[i] = BISHOP;
			break;
		case 'q':
			this->Piece[i] = QUEEN;
			break;
		case 'n':
			this->Piece[i] = KNIGHT;
			break;
		case 'k':
			this->Piece[i] = KING;
			break;
		case 'x':
			this->Color[i] = EMPTY;
			this->Piece[i] = EMPTY;
			break;
		default:
			return 0;
			break;
		}
		switch (char_color_aux) {
		case 'w':
			this->Color[i] = WHITE;
			if (char_aux == 'k') {
				this->WhiteKingPosition = i;
			}
			break;
		case 'b':
			this->Color[i] = BLACK;
			if (char_aux == 'k') {
				this->BlackKingPosition = i;
			}
			break;
		default:
			return 0;
			break;
		}
	}
	return 1;
}

// TODO check what happens when its a king that has to change place in ini position
void Board::change_piece_position(int piece_type, int color, int p_ini, int p_fin) {
	
	this->colorSwaping = this->Color[p_fin];
	this->pieceSwaping = this->Piece[p_fin];

	this->Color[p_ini] = EMPTY;
	this->Piece[p_ini] = EMPTY;
	
	this->Piece[p_fin] = piece_type;
	this->Color[p_fin] = color;

	if (piece_type == KING) {
		if (color == WHITE) {
			this->WhiteKingPosition = p_fin;
		}
		else {
			this->BlackKingPosition = p_fin;
		}
	}
}


void Board::return_piece_position(int piece_type, int color, int p_ini, int p_fin) {
	
	this->Piece[p_fin] = piece_type;
	this->Color[p_fin] = color;
	
	this->Color[p_ini] = this->colorSwaping;
	this->Piece[p_ini] = this->pieceSwaping;

	if (piece_type == KING) {
		if (color == WHITE) {
			this->WhiteKingPosition = p_fin;
		}
		else {
			this->BlackKingPosition = p_fin;
		}
	}
}


bool Board::is_king_NOT_in_check(int color) {
	clean_threadmap(this->threadmap);
	generate_threadmap(this, color, this->threadmap);

	if (color == WHITE) {
		if (this->threadmap[this->WhiteKingPosition] != 1) {
			return true;
		}
		return false;
	}
	else {
		if (this->threadmap[this->BlackKingPosition] != 1) {
			return true;
		}
		return false;
	}	
}

// Will asume that the fen string is right
// TODO Check if string is realy valid
// TODO Check casting and en pessant information in fen string
int Board::parse_fen_description(std::string fen_str) {
	int squares_filled = 0;
	int string_parser = 0;
	char aux_char;
	
	while (squares_filled < 64) {
		aux_char = fen_str[string_parser];

		if (isdigit(aux_char)) {
			for (int k = 0; k < atoi(&aux_char); k++) {
				this->Piece[squares_filled] = EMPTY;
				this->Color[squares_filled] = EMPTY;
				squares_filled++;
			}
		} else if (aux_char == '/') {

		} else {
			if (isupper(aux_char)) {
				this->Color[squares_filled] = WHITE;
			} else {
				this->Color[squares_filled] = BLACK;
			}
			switch (toupper(aux_char)) {
			case 'P': this->Piece[squares_filled] = PAWN; break;
			case 'R': this->Piece[squares_filled] = ROOK; break;
			case 'B': this->Piece[squares_filled] = BISHOP; break;
			case 'N': this->Piece[squares_filled] = KNIGHT; break;
			case 'Q': this->Piece[squares_filled] = QUEEN; break;
			case 'K': this->Piece[squares_filled] = KING; 
				if (isupper(aux_char)) {
					this->WhiteKingPosition = squares_filled;
				}
				else {
					this->BlackKingPosition = squares_filled;
				}
				break;
			default:
				break;
			}
			squares_filled++;
		}
		string_parser++;
	}
	switch (fen_str[++string_parser]) {
	case 'w':
		return WHITE;
	case 'b':
		return BLACK;
	default:
		return 0;
	}
}

void Board::reset(int type) {
	if (type == 0) {
		for (int i = 0; i < 64; i++) {
			this->Piece[i] = EMPTY;
			this->Color[i] = EMPTY;
		}
	}
	else {
		for (int i = 0; i < 64; i++) {
			this->Piece[i] = INITIAL_PIECE_DISTRIBUTION[i];
			this->Color[i] = INITIAL_COLOR_DISTRIBUTION[i];
		}
	}
}
