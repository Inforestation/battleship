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
    hitOnce = 1,
    hitMoreThanOnce = 2,
    mishit = 3
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
    
private:
    
    void generateShipSD();
    void generateShipDD();
    void generateShipTD();
    void generateShipFD();
    
    void stateMachine(board boardPlayer);
    guessingState state;
    
    string previouslyNotHitGuess(board boardPlayer);
    string previouslyHitGuess();
    string previouslyHitOnceGuess(board boardPlayer);
    
    string getFinalGuess(board boardPlayer, string finalGuess);
    direction findShipDirection(string shipSquareCoords[2]);
    
    bool lastTurnHit = false;
    bool hitAtLeastTwice = false;
    string lastGuesses[2];
    string lastTurnGuess;
};
