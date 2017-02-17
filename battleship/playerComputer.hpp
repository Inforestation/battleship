#ifndef playerComputer_hpp
#define playerComputer_hpp
#endif /* playerComputer_hpp */

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <iostream>
using namespace std;

enum guessingState {
    
    previouslyNotHit = 0,
    previouslyHit = 1,
};

enum direction {
    
    vertical = 0,
    horizontal = 1
};

class playerComputer {
    
public:

    string guess;
    void prepareBoard();
    string generateGuess(board boardPlayer);
    board boardComputer;
    playerComputer();
    void updateState();
    int hitCounter;
    
private:
    
    void generateShipSD();
    void generateShipDD();
    void generateShipTD();
    void generateShipFD();
    
    void stateMachine(board boardPlayer);
    guessingState state;
    
    string previouslyNotHitGuess(board boardPlayer);
    string previouslyHitGuess();
    string previouslyHitGuess(board boardPlayer);
    
    int finalSquareDirection;
    
    string getFinalGuess(board boardPlayer, string finalGuess);
    direction findShipDirection(string shipSquareCoords[2]);
    
    string lastGuesses[2];
    string lastTurnGuess;
};
