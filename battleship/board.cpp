#include "board.hpp"
#include <iostream>
using namespace std;

/////////////// GLOBAL ////////////////

struct parsedCoords {
    
    int letter;
    int number;
};

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

parsedCoords stringCoordsParser(string stringCoords) {
    
    parsedCoords coords;
    
    if(stringCoords.length() == 2) {
        
        coords.number = stringCoords[1] - 49;
    }
    
    else if(stringCoords.length() == 3) {
        
        coords.number = ((stringCoords[1] - 48) * 10 + (stringCoords[2] - 48)) - 1;
    }
    
    coords.letter = stringCoords[0] - 65;
    
    return coords;
}

/////////////// checking if the address is valid

bool validAddress (string stringCoords) {
    
    parsedCoords coordinates = stringCoordsParser(stringCoords);
    
    if(coordinates.number <= boardDimension && coordinates.number >= 0 && coordinates.letter <= boardDimension && coordinates.letter >= 0) {
       
        return true;
    }
    
    else {
        
        return false;
    }
}

/////////////// setting adjacent squares

void board::setSquaresAdjacentToShip(square tempShip) {
    
    parsedCoords shipCoorinates = stringCoordsParser(tempShip.address);

    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            
            int currentSquareCoords[2] = {(shipCoorinates.number + x), (shipCoorinates.letter + y)};
            
            if(currentSquareCoords[0] <= boardDimension - 1 && currentSquareCoords[0] >= 0 && currentSquareCoords[1]<= boardDimension - 1 && \
               currentSquareCoords[1] >= 0) {
                if(boardOfSquares[currentSquareCoords[0]][currentSquareCoords[1]].type != ship) {
                
                    boardOfSquares[currentSquareCoords[0]][currentSquareCoords[1]].isAdjacentToShip = true;
                }
            }
        }
    }
}

bool ShipSquaresAreAdjacentDD(string doubleDeckerCoords[doubleDeckerSize]) {
    
    parsedCoords square1 = stringCoordsParser(doubleDeckerCoords[0]);
    parsedCoords square2 = stringCoordsParser(doubleDeckerCoords[1]);
    
    bool hor1 = (square1.number == square2.number && square1.letter == square2.letter + 1);
    bool hor2 = (square1.number == square2.number && square1.letter + 1 == square2.letter);
    bool ver1 = (square1.number == square2.letter && square1.letter == square2.letter);
    bool ver2 = (square1.letter == square2.number && square1.letter == square2.letter);
    
    if(hor1 || hor2 || ver1 || ver2) {
        
        return true;
    }
    
    else {
        
        return false;
    }
}

/////////////// setting the middle square's addresses in...

//// ... three deckers

string setThreeDeckersMiddleSquare(string closingSquareAddressStart, string closingSquareAddressEnd) {
    
    string threeDeckerMiddleSquareCoord;
    
    parsedCoords parsedAddressStart = stringCoordsParser(closingSquareAddressStart);
    parsedCoords parsedAddressEnd = stringCoordsParser(closingSquareAddressEnd);

    threeDeckerMiddleSquareCoord[0] = (parsedAddressStart.number + parsedAddressEnd.number) / 2;
    threeDeckerMiddleSquareCoord[1] = (parsedAddressStart.letter + parsedAddressEnd.letter) / 2;
    
    return threeDeckerMiddleSquareCoord;
    
}

//    
//    string leftOrTopSquare;
//    string rightOrBottomSquare;
//    
//    // which of the squares is the top/right one?
//    if(stringCoordsParser(closingSquareAddress1)[0] < stringCoordsParser(closingSquareAddress2)[0]
//       || stringCoordsParser(closingSquareAddress1)[1] < stringCoordsParser(closingSquareAddress2)[1]) {
//        
//        leftOrTopSquare = closingSquareAddress1;
//    }
//    
//    else {
//        
//        rightOrBottomSquare = closingSquareAddress2;
//    }
//    
//    //if ship is horizontal
//    if(stringCoordsParser(leftOrTopSquare)[0] == stringCoordsParser(rightOrBottomSquare)[0]) {
//
//            threeDeckerMiddleSquareCoord[0] = leftOrTopSquare[0];
//            threeDeckerMiddleSquareCoord[1] = leftOrTopSquare[1] + 1;
//            
//            return threeDeckerMiddleSquareCoord;
//    }
//    
//    //if ship is vertical
//    else {
//            
//            threeDeckerMiddleSquareCoord[0] =leftOrTopSquare[0] + 1;
//            threeDeckerMiddleSquareCoord[1] = leftOrTopSquare[1];
//            
//            return threeDeckerMiddleSquareCoord;
//    }
//}

//// ... four deckers

//string fourDeckerMiddleSquaresCoords[2];
//
//string *setFourDeckersMiddleSquares(string closingSquareAddress1, string closingSquareAddress2) {
//    
//    string leftOrTopSquare;
//    string rightOrBottomSquare;
//    
//    // which of the squares is the top/right one?
//    if(stringCoordsParser(closingSquareAddress1)[0] < stringCoordsParser(closingSquareAddress2)[0]
//       || stringCoordsParser(closingSquareAddress1)[1] < stringCoordsParser(closingSquareAddress2)[1]) {
//        
//        leftOrTopSquare = closingSquareAddress1;
//    }
//    
//    else {
//        
//        rightOrBottomSquare = closingSquareAddress2;
//    }
//    
//    //if ship is horizontal
//    if(stringCoordsParser(leftOrTopSquare)[0] == stringCoordsParser(rightOrBottomSquare)[0]) {
//            
//            (fourDeckerMiddleSquaresCoords[0])[0] = leftOrTopSquare[0];
//            (fourDeckerMiddleSquaresCoords[0])[1] = leftOrTopSquare[1] + 1;
//            
//            (fourDeckerMiddleSquaresCoords[1])[0] = leftOrTopSquare[0];
//            (fourDeckerMiddleSquaresCoords[1])[1] = leftOrTopSquare[1] + 2;
//            
//            return fourDeckerMiddleSquaresCoords;
//    }
//    
//    //if ship is vertical
//    else {
//            
//            (fourDeckerMiddleSquaresCoords[0])[0] = leftOrTopSquare[0] + 1;
//            (fourDeckerMiddleSquaresCoords[0])[1] = leftOrTopSquare[1];
//            
//            (fourDeckerMiddleSquaresCoords[1])[0] = leftOrTopSquare[0] + 2;
//            (fourDeckerMiddleSquaresCoords[1])[1] = leftOrTopSquare[1];
//            
//            return fourDeckerMiddleSquaresCoords;
//    }
//}

/////////////// CREATING SHIPS ////////////////

///////////////// creating single decker(s)

bool board::createSingleDecker(string singleDeckerCoord) {
    
    parsedCoords coords = stringCoordsParser(singleDeckerCoord);
    
    if(boardOfSquares[coords.number][coords.letter].type != ship && validAddress (singleDeckerCoord)) {
        
        tabSingleDecker[singleDeckerIndex].singleDeckerAdress = singleDeckerCoord;
        singleDeckerIndex++;
        
        boardOfSquares[coords.number][coords.letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords.number][coords.letter];
        setSquaresAdjacentToShip(tempShipSquare);
    }
    
    else {
        
        return false;
    }
    
    return true;
}

/////////////// creating double decker(s)

bool board::createDoubleDecker(string doubleDeckerCoords[doubleDeckerSize]) {
    
    parsedCoords coords[2];
    
    coords[0] = stringCoordsParser(doubleDeckerCoords[0]);
    coords[1] = stringCoordsParser(doubleDeckerCoords[1]);
    
    bool isntShip1 = (boardOfSquares[coords[0].number][coords[0].letter].type != ship);
    bool isntShip2 = (boardOfSquares[coords[1].number][coords[1].letter].type != ship);
    
    if(isntShip1 && isntShip2 && ShipSquaresAreAdjacentDD(doubleDeckerCoords) && validAddress(doubleDeckerCoords[0]) && validAddress(doubleDeckerCoords[1])) {
        
        tabDoubleDecker[doubleDeckerIndex].doubleDeckerAdress[0] = doubleDeckerCoords[0];
        tabDoubleDecker[doubleDeckerIndex].doubleDeckerAdress[1] = doubleDeckerCoords[1];
        doubleDeckerIndex++;
        
        boardOfSquares[coords[0].number][coords[0].letter].type = ship;
        boardOfSquares[coords[1].number][coords[1].letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords[0].number][coords[0].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coords[1].number][coords[1].letter];
        setSquaresAdjacentToShip(tempShipSquare);
    }
    
    else {
        
        return false;
    }
    
    return true;
}

/////////////// creating three decker(s)

bool board::createThreeDecker(string threeDeckerCoords[2]) {
    
    string middleSquareCoords = setThreeDeckersMiddleSquare(threeDeckerCoords[0], threeDeckerCoords[1]);
    parsedCoords coordsMiddle = stringCoordsParser(middleSquareCoords);
    parsedCoords coords[2];
    
    coords[0] = stringCoordsParser(threeDeckerCoords[0]);
    coords[1] = stringCoordsParser(threeDeckerCoords[1]);
    
    bool isntShip1 = boardOfSquares[coords[0].number][coords[0].letter].type != ship;
    bool isntShip2 = boardOfSquares[coords[1].number][coords[1].letter].type != ship;
    bool isntShip3 = boardOfSquares[coordsMiddle.number][coordsMiddle.letter].type != ship;
    bool TDvalidAddress = validAddress(threeDeckerCoords[0]) && validAddress(threeDeckerCoords[1]) && validAddress(middleSquareCoords);
    
    if(isntShip1 && isntShip2 && isntShip3 && TDvalidAddress) {
        
        for(int y = 0; y < threeDeckerSize; y++) {
            
            tabThreeDecker[threeDeckerIndex].threeDeckerAdress[y] = threeDeckerCoords[y];
            boardOfSquares[coords[y].number][coords[y].letter].type = ship;
            
            tempShipSquare = boardOfSquares[coords[y].number][coords[y].letter];
            setSquaresAdjacentToShip(tempShipSquare);
        }
    
        threeDeckerIndex++;
    }
    
    else {
        
        return false;
    }
    
    return true;

}

/////////////// creating four decker

//bool board::createFourDecker(string fourDeckerCoords[2]) {
//    
//    fourDeckerCoords[1] = (setFourDeckersMiddleSquares(fourDeckerCoords[0], fourDeckerCoords[3]))[0];
//    fourDeckerCoords[2] = (setFourDeckersMiddleSquares(fourDeckerCoords[0], fourDeckerCoords[3]))[1];
//    
//    bool isntShip1 = boardOfSquares[stringCoordsParser(fourDeckerCoords[0])[0]][stringCoordsParser(fourDeckerCoords[0])[1]].type != ship;
//    bool isntShip2 = boardOfSquares[stringCoordsParser(fourDeckerCoords[1])[0]][stringCoordsParser(fourDeckerCoords[1])[1]].type != ship;
//    bool isntShip3 = boardOfSquares[stringCoordsParser(fourDeckerCoords[2])[0]][stringCoordsParser(fourDeckerCoords[2])[1]].type != ship;
//    bool isntShip4 = boardOfSquares[stringCoordsParser(fourDeckerCoords[3])[0]][stringCoordsParser(fourDeckerCoords[3])[1]].type != ship;
//    bool FDvalidAddress = validAddress(fourDeckerCoords[0]) && validAddress(fourDeckerCoords[1]) && validAddress(fourDeckerCoords[2]) && validAddress(fourDeckerCoords[3]);
//    
//    if(isntShip1 && isntShip2 && isntShip3 && isntShip4 && FDvalidAddress) {
//        
//        int *FDIntCoords[fourDeckerSize];
//        
//        for(int x = 0; x < fourDeckerSize; x++) {
//            
//            FDIntCoords[x] = stringCoordsParser(fourDeckerCoords[x]);
//        }
//        
//        for(int a = 0; a <= fourDeckerSize - 1; a++) {
//           
//            fourDecker.fourDeckerAdress[a] = fourDeckerCoords[a];
//            
//            boardOfSquares[*FDIntCoords[a]][*(FDIntCoords[a] + 1)].type = ship;
//            
//            tempShipSquare = boardOfSquares[*FDIntCoords[a]][*(FDIntCoords[a] + 1)];
//            setSquaresAdjacentToShip(tempShipSquare);
//        }
//    }
//    
//    else {
//        
//        return false;
//    }
//    
//    return true;
//}

void board::showBoard() {
    
        cout << "   A B C D E F G H I J" << endl;
    
    for(int row = 0; row < boardDimension; row++) {
        
        if(row != boardDimension - 1) {
            
            cout << row + 1 << "  ";
        }
        
        else {
            
            cout << row + 1 << " ";
        }
        
        for(int column = 0; column < boardDimension; column++) {
            
            if(boardOfSquares[row][column].type == ship) {
                
                cout << "o";
            }
            
            else if(boardOfSquares[row][column].isAdjacentToShip == true) {
                    
                cout << "A";
            }
                
            else {
                    
                cout << ".";
            }
            
            cout << " ";
        }
        
        cout << endl;
    }
    
    cout << endl << endl;
}








