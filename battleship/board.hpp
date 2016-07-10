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

const int singleDeckerNumber = 4;
const int doubleDeckerNumber = 3;
const int threeDeckerNumber = 2;
const int fourDeckerNumber = 1;

// Stores and controls the elements on the board

class board{
    
public:
    int hitCount;
    int missCount;
    int emptyCount;
    bool isReadyToPlay;
    
    class ship tabSingleDecker[singleDeckerNumber];
    class ship tabDoubleDecker[doubleDeckerNumber];
    class ship tabThreeDecker[threeDeckerNumber];
    class ship tabFourDecker[fourDeckerNumber];
    
    int singleDeckerIndex = 0;
    int doubleDeckerIndex = 0;
    int threeDeckerIndex = 0;
    
    square boardOfSquares[boardDimension][boardDimension];
    
    bool createSingleDecker(string singleDeckerCoord);
    bool createDoubleDecker(string doubleDeckerCoords[doubleDeckerSize]);
    
    void setSquaresAdjacentToSingleDecker();
    board();
};
