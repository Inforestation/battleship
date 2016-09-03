#include "board.hpp"
#include <iostream>
using namespace std;

/////////////// GLOBAL ////////////////


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

///////////////// ADDITIONAL FUNCTIONS ///////////////////

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
    
    if(coordinates.number < boardDimension && coordinates.number >= 0 && coordinates.letter < boardDimension && coordinates.letter >= 0) {
       
        return true;
    }
    
    else {
        
        return false;
    }
}

/////////////// adjacent squares functions

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

bool shipSquaresAreAdjacentDD(string doubleDeckerCoords[2]) {
    
    parsedCoords square1 = stringCoordsParser(doubleDeckerCoords[0]);
    parsedCoords square2 = stringCoordsParser(doubleDeckerCoords[1]);
    
    bool hor1 = (square1.letter == square2.letter && square1.number == square2.number + 1);
    bool hor2 = (square1.letter == square2.letter && square1.number + 1 == square2.number);
    bool ver1 = (square1.number == square2.number && square1.letter + 1 == square2.letter);
    bool ver2 = (square1.number == square2.number && square1.letter == square2.letter + 1);
    
    if(hor1 || hor2 || ver1 || ver2) {
        
        return true;
    }
    
    else {
        
        return false;
    }
}

bool shipSquaresAreAdjacentTD(string threeDeckerCoords[2], string middleSquareCoords) {
    
    parsedCoords squareStart = stringCoordsParser(threeDeckerCoords[0]);
    parsedCoords squareMiddle = stringCoordsParser(middleSquareCoords);
    parsedCoords squareEnd = stringCoordsParser(threeDeckerCoords[1]);

    bool hor1 = (squareStart.letter == squareMiddle.letter && squareStart.number == squareMiddle.number + 1);
    bool hor2 = (squareStart.letter == squareMiddle.letter && squareStart.number + 1 == squareMiddle.number);
    bool ver1 = (squareStart.number == squareMiddle.number && squareStart.letter == squareMiddle.letter + 1);
    bool ver2 = (squareStart.number == squareMiddle.number && squareStart.letter + 1 == squareMiddle.letter);
    
    bool hor3 = (squareEnd.letter == squareMiddle.letter && squareEnd.number == squareMiddle.number + 1);
    bool hor4 = (squareEnd.letter == squareMiddle.letter && squareEnd.number + 1 == squareMiddle.number);
    bool ver3 = (squareEnd.number == squareMiddle.number && squareEnd.letter == squareMiddle.letter + 1);
    bool ver4 = (squareEnd.number == squareMiddle.number && squareEnd.letter + 1 == squareMiddle.letter);
    
    if((hor1 || hor2 || ver1 || ver2) && (hor3 || hor4 || ver3 || ver4)) {
        
        return true;
    }
    
    else {
        
        return false;
    }
}

bool shipSquaresAreAdjacentFD(string fourDeckerCoords[2], string middleSquareCoords[2]) {
    
    parsedCoords squareStart = stringCoordsParser(fourDeckerCoords[0]);
    parsedCoords squareMiddle1 = stringCoordsParser(middleSquareCoords[0]);
    parsedCoords squareMiddle2 = stringCoordsParser(middleSquareCoords[1]);
    parsedCoords squareEnd = stringCoordsParser(fourDeckerCoords[1]);
    
    bool hor1 = (squareStart.letter == squareMiddle1.letter && squareStart.number == squareMiddle1.number + 1);
    bool hor2 = (squareStart.letter == squareMiddle1.letter && squareStart.number + 1 == squareMiddle1.number);
    bool ver1 = (squareStart.number == squareMiddle1.number && squareStart.letter == squareMiddle1.letter + 1);
    bool ver2 = (squareStart.number == squareMiddle1.number && squareStart.letter + 1 == squareMiddle1.letter);
    
    bool hor3 = (squareMiddle1.letter == squareMiddle2.letter && squareMiddle1.number == squareMiddle2.number + 1);
    bool hor4 = (squareMiddle1.letter == squareMiddle2.letter && squareMiddle1.number + 1 == squareMiddle2.number);
    bool ver3 = (squareMiddle1.number == squareMiddle2.number && squareMiddle1.letter == squareMiddle2.letter + 1);
    bool ver4 = (squareMiddle1.number == squareMiddle2.number && squareMiddle1.letter + 1 == squareMiddle2.letter);
    
    bool hor5 = (squareMiddle2.letter == squareEnd.letter && squareMiddle2.number == squareEnd.number + 1);
    bool hor6 = (squareMiddle2.letter == squareEnd.letter && squareMiddle2.number + 1 == squareEnd.number);
    bool ver5 = (squareMiddle2.number == squareEnd.number && squareMiddle2.letter == squareEnd.letter + 1);
    bool ver6 = (squareMiddle2.number == squareEnd.number && squareMiddle2.letter + 1 == squareEnd.letter);
    
    if((hor1 || hor2 || ver1 || ver2) && (hor3 || hor4 || ver3 || ver4) && (hor5 || hor6 || ver5 || ver6)) {
        
        return true;
    }
    
    else {
        
        return false;
    }
}

bool board::isntAdjacentToShip(parsedCoords coord) {
    
    if(boardOfSquares[coord.number][coord.letter].isAdjacentToShip == false) {
        
        return true;
    }
    
    return false;
}

bool board::isAvailable(parsedCoords coords) {
    
    if((boardOfSquares[coords.number][coords.letter].type != ship) && isntAdjacentToShip(coords)) {
        
        return true;
    }
    return false;
}

/////////////// setting the middle square's addresses in...

//// ... three deckers

string setThreeDeckersMiddleSquare(string closingSquareAddressStart, string closingSquareAddressEnd) {
    
    string threeDeckerMiddleSquareCoords = "";
    
    parsedCoords parsedAddressStart = stringCoordsParser(closingSquareAddressStart);
    parsedCoords parsedAddressEnd = stringCoordsParser(closingSquareAddressEnd);

    threeDeckerMiddleSquareCoords = threeDeckerMiddleSquareCoords + char(((parsedAddressStart.letter + parsedAddressEnd.letter) / 2) + 65);
    threeDeckerMiddleSquareCoords = threeDeckerMiddleSquareCoords + to_string((parsedAddressStart.number + parsedAddressEnd.number) / 2 + 1);
    
    return threeDeckerMiddleSquareCoords;
}

//// ... four deckers

string setFourDeckersMiddleSquares(string closingSquareAddress1, string closingSquareAddress2) {
    
    string addedMiddleSquaresCoords;
    
    string leftOrTopSquare;
    string rightOrBottomSquare;
    
    parsedCoords closing1 = stringCoordsParser(closingSquareAddress1);
    parsedCoords closing2 = stringCoordsParser(closingSquareAddress2);
    
    // which of the squares is the top/right one?
    if(closing1.number < closing2.number || closing1.letter < closing2.letter) {
        
        leftOrTopSquare = closingSquareAddress1;
        rightOrBottomSquare = closingSquareAddress2;
    }
    
    else {
        
        leftOrTopSquare = closingSquareAddress2;
        rightOrBottomSquare = closingSquareAddress1;
    }
    
    parsedCoords leftTop = stringCoordsParser(leftOrTopSquare);
    parsedCoords rightBottom = stringCoordsParser(rightOrBottomSquare);
    
    //if ship is horizontal
    if(leftTop.number == rightBottom.number) {
            
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + char(leftOrTopSquare[0] + 1);
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + to_string(leftTop.number + 1);
        
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + '#';
        
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + char(leftOrTopSquare[0] + 2);
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + to_string(leftTop.number + 1);
    }
    
    //if ship is vertical
    else {
            
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + leftOrTopSquare[0];
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + to_string(leftTop.number + 2);
        
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + '#';
        
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + leftOrTopSquare[0];
        addedMiddleSquaresCoords = addedMiddleSquaresCoords + to_string(leftTop.number + 3);
    }
    
    return addedMiddleSquaresCoords;
}

/////////////// CREATING SHIPS ////////////////

///////////////// creating a single decker

bool board::createSingleDecker(string singleDeckerCoords) {
    
    parsedCoords coords = stringCoordsParser(singleDeckerCoords);
    
    if(!(validAddress(singleDeckerCoords))) {
        
        cout << "Error: Given coordinates (" << singleDeckerCoords << ") aren't valid." << endl;
        
        return false;
    }
    
    else if(!(isAvailable(coords))) {
        
        cout << "Error: Given coordinates (" << singleDeckerCoords << ") aren't available." << endl;
        
        return false;
    }
    
    else if(singleDeckerIndex > singleDeckerNumber) {

        return false;
    }
    
    else {
        
        tabSingleDecker[singleDeckerIndex].singleDeckerAdress = singleDeckerCoords;
        singleDeckerIndex++;
        
        boardOfSquares[coords.number][coords.letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords.number][coords.letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        cout << "Setting a ship (single decker) successful." << endl;
        
         return true;
    }
}

/////////////// creating a double decker

bool board::createDoubleDecker(string doubleDeckerCoords[doubleDeckerSize]) {
    
    parsedCoords coords[2];
    
    coords[0] = stringCoordsParser(doubleDeckerCoords[0]);
    coords[1] = stringCoordsParser(doubleDeckerCoords[1]);
    
    if(!(validAddress(doubleDeckerCoords[0])) && !(validAddress(doubleDeckerCoords[1]))) {
        
        cout << "Error: Given coordinates (" << doubleDeckerCoords[0]  << " or / and " << doubleDeckerCoords[1] << ") aren't valid." << endl;
        
        return false;
    }
    
    else if(!(isAvailable(coords[0])) && !(isAvailable(coords[1]))) {
        
        cout << "Error: Given coordinates (" << doubleDeckerCoords[0]  << " or / and " << doubleDeckerCoords[1] << ") aren't available." << endl;
        
        return false;
    }
    
    else if(!(shipSquaresAreAdjacentDD(doubleDeckerCoords))) {
        
        cout << "Error: Ship squares (" << doubleDeckerCoords[0] << " and " << doubleDeckerCoords[1] << ") aren't adjacent." << endl;
        
        return false;
    }
    
    
    
    else if(doubleDeckerIndex > doubleDeckerNumber) {
        
        return false;
    }
    
    else {
        
        tabDoubleDecker[doubleDeckerIndex].doubleDeckerAdress[0] = doubleDeckerCoords[0];
        tabDoubleDecker[doubleDeckerIndex].doubleDeckerAdress[1] = doubleDeckerCoords[1];
        doubleDeckerIndex++;
        
        boardOfSquares[coords[0].number][coords[0].letter].type = ship;
        boardOfSquares[coords[1].number][coords[1].letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords[0].number][coords[0].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coords[1].number][coords[1].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        cout << "Setting a ship (double decker) successful." << endl;
        
        return true;
    }
}

/////////////// creating a three decker

bool board::createThreeDecker(string threeDeckerCoords[2]) {
    
    string middleSquareCoords = setThreeDeckersMiddleSquare(threeDeckerCoords[0], threeDeckerCoords[1]);
    parsedCoords coordsMiddle = stringCoordsParser(middleSquareCoords);
    parsedCoords coords[2];
    
    coords[0] = stringCoordsParser(threeDeckerCoords[0]);
    coords[1] = stringCoordsParser(threeDeckerCoords[1]);
    
    if(!(validAddress(threeDeckerCoords[0])) && !(validAddress(middleSquareCoords)) && !(validAddress(threeDeckerCoords[1]))) {
        
        cout << "Error: Given coordinates aren't valid." << endl;
        
        return false;
    }
    
    else if(!(isAvailable(coords[0])) && !(isAvailable(coordsMiddle)) && !(isAvailable(coords[1]))) {
        
        cout << "Error: Given coordinates aren't available" << endl;
        
        return false;
    }
    
    else if(!(shipSquaresAreAdjacentTD(threeDeckerCoords, middleSquareCoords))) {
        
        cout << "Error: Ship squares aren't adjacent." << endl;
        
        return false;
    }
    
    else if(threeDeckerIndex > threeDeckerNumber) {
        
        return false;
    }
    
    else {
        
        tabThreeDecker[threeDeckerIndex].threeDeckerAdress[0] = threeDeckerCoords[0];
        tabThreeDecker[threeDeckerIndex].threeDeckerAdress[1] = middleSquareCoords;
        tabThreeDecker[threeDeckerIndex].threeDeckerAdress[2] = threeDeckerCoords[1];
        
        threeDeckerIndex++;
        
        boardOfSquares[coords[0].number][coords[0].letter].type = ship;
        boardOfSquares[coords[1].number][coords[1].letter].type = ship;
        boardOfSquares[coordsMiddle.number][coordsMiddle.letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords[0].number][coords[0].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coords[1].number][coords[1].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coordsMiddle.number][coordsMiddle.letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        cout << "Setting a ship (three decker) successful." << endl;
        
        return true;
    }
}

/////////////// creating a four decker

bool board::createFourDecker(string fourDeckerCoords[2]) {
    
    string addedMiddleSquaresCoords = setFourDeckersMiddleSquares(fourDeckerCoords[0], fourDeckerCoords[1]);
    
    string middleSquaresCoords[2];
    
    string delimiter = "#";
    
    middleSquaresCoords[0] = addedMiddleSquaresCoords.substr(0, addedMiddleSquaresCoords.find(delimiter));
    middleSquaresCoords[1] = addedMiddleSquaresCoords.substr(addedMiddleSquaresCoords.find(delimiter) + 1, addedMiddleSquaresCoords.length());
    
    parsedCoords coordsMiddle[2];
    coordsMiddle[0] = stringCoordsParser(middleSquaresCoords[0]);
    coordsMiddle[1] = stringCoordsParser(middleSquaresCoords[1]);
    
    parsedCoords coords[2];
    coords[0] = stringCoordsParser(fourDeckerCoords[0]);
    coords[1] = stringCoordsParser(fourDeckerCoords[1]);
    
    if(!(validAddress(fourDeckerCoords[0])) && !(validAddress(middleSquaresCoords[0])) && !(validAddress(middleSquaresCoords[1])) && !(validAddress(fourDeckerCoords[1]))) {
        
        cout << "Error: Given coordinates aren't valid." << endl;
        
        return false;
    }
    
    else if(!(isAvailable(coords[0])) && !(isAvailable(coordsMiddle[0])) && !(isAvailable(coordsMiddle[1])) && !(isAvailable(coords[1]))) {
        
        cout << "Error: Given coordinates aren't available" << endl;
        
        return false;
    }
    
    else if(!(shipSquaresAreAdjacentFD(fourDeckerCoords, middleSquaresCoords))) {
        
        cout << "Error: Ship squares aren't adjacent." << endl;
        
        return false;
    }
    
    else if(fourDeckerIndex > fourDeckerNumber) {
    
        return false;
    }
    
    else {
        
        fourDecker.fourDeckerAdress[0] = fourDeckerCoords[0];
        fourDecker.fourDeckerAdress[1] = middleSquaresCoords[0];
        fourDecker.fourDeckerAdress[2] = middleSquaresCoords[1];
        fourDecker.fourDeckerAdress[3] = fourDeckerCoords[1];
        
        fourDeckerIndex++;
        
        boardOfSquares[coords[0].number][coords[0].letter].type = ship;
        boardOfSquares[coords[1].number][coords[1].letter].type = ship;
        boardOfSquares[coordsMiddle[0].number][coordsMiddle[0].letter].type = ship;
        boardOfSquares[coordsMiddle[1].number][coordsMiddle[1].letter].type = ship;
        
        tempShipSquare = boardOfSquares[coords[0].number][coords[0].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coords[1].number][coords[1].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coordsMiddle[0].number][coordsMiddle[0].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        tempShipSquare = boardOfSquares[coordsMiddle[1].number][coordsMiddle[1].letter];
        setSquaresAdjacentToShip(tempShipSquare);
        
        cout << "Setting a ship (four decker) successful." << endl;
        
        return true;
    }
}


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








