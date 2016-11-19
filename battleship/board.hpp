#ifndef board_hpp
#define board_hpp
#include <stdio.h>
using namespace std;
#endif /* board_hpp */

#include <string>

#ifndef square_hpp
#define square_hpp
#include "square.hpp"
#endif /* square_hpp */

struct parsedCoords {
    
    int letter;
    int number;
};

enum guessResult {
    
    miss = 0,
    hit = 1,
    sunk = 2
};

const int boardDimension = 10;
const int doubleDeckerSize = 2;
const int threeDeckerSize = 3;
const int fourDeckerSize = 4;

extern const int singleDeckerNumberDefault;
extern const int doubleDeckerNumberDefault;
extern const int threeDeckerNumberDefault;
extern const int fourDeckerNumberDefault;

const int maxDeckerNumber = fourDeckerNumberDefault;

// Stores and controls elements on the board

class board {
    
public:
    int singleDeckerNumber;
    int doubleDeckerNumber;
    int threeDeckerNumber;
    int fourDeckerNumber;
    
    int singleDeckerIndex;
    int doubleDeckerIndex;
    int threeDeckerIndex;
    int fourDeckerIndex;
    
    int hitCount;
    int missCount;
    int emptyCount;
    bool isReadyToPlay;
    
    square tempShipSquare;
    
    square boardOfSquares[boardDimension][boardDimension];
    
    bool createSingleDecker(string singleDeckerCoord);
    bool createDoubleDecker(string doubleDeckerCoords[doubleDeckerSize]);
    bool createThreeDecker(string threeDeckerCoords[threeDeckerSize]);
    bool createFourDecker(string fourDeckerCoords[fourDeckerSize]);
    
    void showBoard(bool showUnknownShips);
    guessResult hitSquare(string guess);
    bool isSunk(string &guess);
    bool hasGameEnded();
    
    board();
    
    board(board const &boardToCopy);
    
private:
    bool isAvailable(parsedCoords coords);
    bool isntAdjacentToShip(parsedCoords coord);
    void setSquaresAdjacentToShip(square tempShip);
};
