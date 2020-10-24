#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "binsudoku.h"

int main(){
	/* world's hardest sudoku */
	std::vector<uint32_t> v1 = {
	    0, 0, 5, 3, 0, 0, 0, 0, 0, 
	    8, 0, 0, 0, 0, 0, 0, 2, 0, 
	    0, 7, 0, 0, 1, 0, 5, 0, 0, 
	    4, 0, 0, 0, 0, 5, 3, 0, 0, 
	    0, 1, 0, 0, 7, 0, 0, 0, 6, 
	    0, 0, 3, 2, 0, 0, 0, 8, 0, 
	    0, 6, 0, 5, 0, 0, 0, 0, 9,
	    0, 0, 4, 0, 0, 0, 0, 3, 0, 
	    0, 0, 0, 0, 0, 9, 7, 0, 0};

	/* really hard sudoku for backtracking */
	std::string str("..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9");

    Sudoku S1(v1);
    Sudoku S2(str);
    bool with_timing = true;
    if (S1.solve(with_timing)) {
        S1.print();
        std::cout << "elapsed time: " << S1.getRuntime() << "s\n";
    }
    if (S2.solve(with_timing)){
    	S2.print();
        std::cout << "elapsed time: " << S2.getRuntime() << "s\n";
    }
    return 0;
}