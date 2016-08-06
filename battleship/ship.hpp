#ifndef ship_hpp
#define ship_hpp
#include <stdio.h>
#endif /* ship_hpp */
using namespace std;
#include "square.hpp"

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

class ship : public square {
    
public:
    shipType type;
    shipState state;
    
    string singleDeckerAdress;
    string doubleDeckerAdress[2];
    string threeDeckerAdress[3];
    string fourDeckerAdress[4];
    
    ship() {}
    ship(shipType inType, shipState inState);
};