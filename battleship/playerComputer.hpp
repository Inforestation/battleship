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

class playerComputer {
    
public:

    void prepareBoard();
    board boardComputer;
    playerComputer();
    string generateGuess();
    
private:
    
    void generateShipSD();
    void generateShipDD();
    void generateShipTD();
    void generateShipFD();
    
    string previouslyNotHitGuess();
    string previouslyHitGuess();
    string previouslyHitOnceGuess();
    
    bool lastTurnHit = false;
    bool hitAtLeastTwice = false;
    string lastTurnGuess;
};
