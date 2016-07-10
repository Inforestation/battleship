#ifndef square_hpp
#define square_hpp
#include <stdio.h>
#include <string>
#endif /* square_hpp */

using namespace std;

enum squareType {
    
    empty = 0,
    ship = 1
};

enum squareState {
    
    unknown = 0,
    guessed = 1
};

class square {
    
public:
    bool isAdjacentToShip;
    squareType type;
    squareState state;
    string address;
    
    square();
    square(squareType inType, squareState inState);
};
