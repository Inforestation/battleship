#ifndef square_hpp
#define square_hpp

#include <stdio.h>

#endif /* square_hpp */

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
    squareType type;
    squareState state;
    
    square();
    square(squareType inType, squareState inState);
};
