#include <iostream>

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

#ifndef gamePlot_hpp
#define gamePlot_hpp
#include "gamePlot.hpp"
#endif /* gamePlot_hpp */

using namespace std;

int main() {
    
    gamePlot plot;
    
    cout << "!" << endl << endl;
    
    return 0;
}

// 1. computer playing mechanics
//      1a. not guessing already guessed squares --
//      1b. when square is hit, computer continues to guess near this square
//      1c. if only mDecker are left, computer hits only the possibe squares
//2. when hit and sunk, all adjacent squares are set as guessed --



