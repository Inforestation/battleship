#ifndef square_hpp
#define square_hpp
#include <stdio.h>
#include <string>
#endif /* square_hpp */

using namespace std;

enum squareType {       // is a virtue of a square on a board: either empty or ship (x-decker)
    
    empty = 0,
    singleDecker = 1,
    doubleDecker = 2,
    threeDecker = 3,
    fourDecker = 4
};

enum squareState {      // is a virtue of a square on a board: has player guessed it yet?
    
    unknown = 0,
    guessed = 1
};

class square {
    
public:
    bool isAdjacentToShip;
    squareType type;
    squareState state;
    string address;
    string associatedSquares[3];
    
    square();
    square(squareType inType, squareState inState);
};
