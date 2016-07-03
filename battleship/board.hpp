#ifndef board_hpp
#define board_hpp
#include <stdio.h>
#include <string>
using namespace std;
#endif /* board_hpp */

#ifndef ship_hpp
#define ship_hpp
#include "ship.hpp"
#endif /* ship_hpp */

#ifndef square_hpp
#define square_hpp
#include "square.hpp"
#endif /* square_hpp */

const int boardDimension = 10;
const int doubleDeckerSize = 2;
const int threeDeckerSize = 3;
const int fourDeckerSize = 4;

// Przechowuje i zarzadza elementami planszy

class board{
    
public:
    int hitCount;
    int missCount;
    int emptyCount;
    bool isReadyToPlay;
    
    square boardOfSquares[boardDimension][boardDimension];
    
    board();
};
