#ifndef gamePlot_hpp
#define gamePlot_hpp
#include <stdio.h>
#endif /* gamePlot_hpp */

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

#include <iostream>
using namespace std;

enum gameState {
    
    initialization = 0,
    creatingBoardPlayer = 1,
    creatingBoardComputer = 2,
    play = 3,
    gameEnd = 4
};

class gamePlot {
    
public:
    gamePlot();
    
private:
    board boardPlayer;
    board boardComputer;
    
    gameState state;
    
    void stateMachine();
};