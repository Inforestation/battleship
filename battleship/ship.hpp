#ifndef ship_hpp
#define ship_hpp
#include <stdio.h>
#endif /* ship_hpp */

enum shipType {
    
    singleDecker = 1,
    twoDecker = 2,
    threeDecker = 3,
    fourDecker = 4,
};

enum shipState {
    
    clear = 0,
    hit = 1,
    sunk = 2
};

class ship {
    
public:
    shipType type;
    shipState state;
    
    ship();
    ship(shipType inType, shipState inState);
};