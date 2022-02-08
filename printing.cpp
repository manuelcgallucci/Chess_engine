#include "printing.h"

void print_array(int* array_p) {
	
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) {
			std::cout << std::endl;
		}	
		if (array_p[i] != 0) {
			std::cout << "x";
		} else {
			std::cout << "o";
		}

	}
}

