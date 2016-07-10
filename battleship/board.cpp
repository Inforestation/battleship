#include "board.hpp"
using namespace std;

/////////////// BOARD CONSTRUCTOR ////////////////

board::board() {
    
    hitCount = 0;
    missCount = 0;
    emptyCount = boardDimension * boardDimension;
    isReadyToPlay = false;
    
    char addressLetter = 65;
    
    for(int a = 0; a < boardDimension; a++) {
        for(int b = 0; b < boardDimension; b++) {
            
            string squareAdress = string(1, addressLetter) + to_string(b + 1);
            
            boardOfSquares[b][a].address = squareAdress;
        }
        addressLetter++;
    }

    for(int a = 0; a < boardDimension; a++) {
        for(int b = 0; b < boardDimension; b++) {
            
            boardOfSquares[b][a].type = empty;
            boardOfSquares[b][a].state = unknown;
            boardOfSquares[b][a].isAdjacentToShip = false;
        }
    }
}

///////////////// CREATING SHIPS ///////////////////

/////////////// changing string coords to int coords

int intCoords[2];

int *stringCoordsParser(string stringCoords) {
    
    intCoords[0] = stringCoords[0] - 65;
    intCoords[1] = stringCoords[1] - 1;
    
    return intCoords;
}

/////////////// setting adjacent squares

void board::setSquaresAdjacentToSingleDecker() {
    
    boardOfSquares[intCoords[0] - 1][intCoords[1]].isAdjacentToShip = true;         // down
    boardOfSquares[intCoords[0] + 1][intCoords[1]].isAdjacentToShip = true;         // up
    boardOfSquares[intCoords[0]][intCoords[1] - 1].isAdjacentToShip = true;         // left
    boardOfSquares[intCoords[0]][intCoords[1] + 1].isAdjacentToShip = true;         // right
    
    boardOfSquares[intCoords[0] - 1][intCoords[1] - 1].isAdjacentToShip = true;     // up-left
    boardOfSquares[intCoords[0] - 1][intCoords[1] + 1].isAdjacentToShip = true;     // up-right
    boardOfSquares[intCoords[0] + 1][intCoords[1] - 1].isAdjacentToShip = true;     // down-left
    boardOfSquares[intCoords[0] + 1][intCoords[1] + 1].isAdjacentToShip = true;     // down-right
}

///////////////

string coordsOfThreeDeckerSquares[threeDeckerSize];

string *setThreeDeckerSquaresAddress(string threeDeckerStringCoords[threeDeckerSize - 1]) {
    
    coordsOfThreeDeckerSquares[0] = threeDeckerStringCoords[0];
    coordsOfThreeDeckerSquares[2] = threeDeckerStringCoords[1];
    
    // setting the middle block
    
    if(stringCoordsParser(coordsOfThreeDeckerSquares[0])[0] == stringCoordsParser(coordsOfThreeDeckerSquares[2])[0]) {
        // if(coordsOfThreeDeckerSquares[0] -> row == coordsOfThreeDeckerSquares[2] -> row)
        
        (coordsOfThreeDeckerSquares[1])[0] = (coordsOfThreeDeckerSquares[0])[0] + 1;
        // address letter (column) of coordsOfThreeDeckerSquares[1] is previous letter + 1 in ASCII
        (coordsOfThreeDeckerSquares[1])[1] = (coordsOfThreeDeckerSquares[0])[1];
        // address number (row) of coordsOfThreeDeckerSquares[1] is same as coordsOfThreeDeckerSquares[0] address number
    }
    
    else {
        
        (coordsOfThreeDeckerSquares[1])[0] = (coordsOfThreeDeckerSquares[0])[0];
        // address letter (column) of coordsOfThreeDeckerSquares[1] is same as coordsOfThreeDeckerSquares[0] address letter
        (coordsOfThreeDeckerSquares[1])[1] = (coordsOfThreeDeckerSquares[0])[1] + 1;
        // address number (row) of coordsOfThreeDeckerSquares[1] is coordsOfThreeDeckerSquares[0] address number + 1

    }
    
    return coordsOfThreeDeckerSquares;
}

///////////////

bool board::createSingleDecker(string singleDeckerCoord) {
   
    stringCoordsParser(singleDeckerCoord);
    
    if(singleDeckerCoord != boardOfSquares[intCoords[0]][intCoords[1]].address) {
        
        tabSingleDecker[singleDeckerIndex].address = singleDeckerCoord; // ? address in 'ship' ?
        boardOfSquares[intCoords[0]][intCoords[1]].type = ship;
        setSquaresAdjacentToSingleDecker();
        
        singleDeckerIndex++;
    }
    
    else {
        
        return false;
    }
    
    return true;
}

bool board:: createDoubleDecker(string doubleDeckerCoords[doubleDeckerSize]) {
    
    
    if(1) {
        
        
    }
    
    else {
        
        return false;
    }
    
    return true;
}




//ship createThreeDecker(string threeDeckerCoords[threeDeckerSize]) {
//    
//}
//
//class ship createFourDecker(string fourDeckerCoords[fourDeckerSize]) {
//    
//}




