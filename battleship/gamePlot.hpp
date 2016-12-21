#ifndef gamePlot_hpp
#define gamePlot_hpp
#include <stdio.h>
#endif /* gamePlot_hpp */

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

#ifndef playerComputer_hpp
#define playerComputer_hpp
#include "playerComputer.hpp"
#endif /* playerComputer_hpp */

#include <iostream>
using namespace std;

enum gameState {
    
    initialization = 0,
    creatingBoardPlayer = 1,
    creatingBoardComputer = 2,
    play = 3,
    gameEnd = 4
};

enum gameplayState {
    
    playerTurn = 0,
    computerTurn = 1,
    gameplayEnd = 2
};

class gamePlot {
    
public:
    gamePlot();
    
private:
   
    playerComputer computer; // playerComputer class' object
    
    board boardPlayer;
    gameState state;
    gameplayState playState;
    
    void stateMachine();
    
    void createBoardPlayer();
    void createBoardComputer();
    void playGame();
    void turnPlayer();
    void turnComputer();
};