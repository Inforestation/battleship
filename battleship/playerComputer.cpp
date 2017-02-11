#include "playerComputer.hpp"
using namespace std;

string createFinalShipAddress(string startAddress, squareType type);

playerComputer::playerComputer() {

    state = previouslyNotHit;
}

/////////////// SETTING COMPUTER'S BOARD ////////////////

/////////////// generating computer's ships

void playerComputer::generateShipSD() {
    
    srand(time(NULL));
    
    string addressLetter;
    string addressNumber;
    
    string fullAddress;
    
    int shipsPlacedNumber = 0;
    
    while(shipsPlacedNumber < singleDeckerNumberDefault) {
        
        addressLetter = (rand() % 10) + 65;
        addressNumber = to_string(rand() % 10 + 1);
        
        fullAddress = addressLetter + addressNumber;
        
        if(boardComputer.createSingleDecker(fullAddress)) {
            
            shipsPlacedNumber++;
        }
    }
}

void playerComputer::generateShipDD() {
    
    srand(time(NULL));
    
    string addressLetter;
    string addressNumber;
    
    string fullAddress[2];
    
    int shipsPlacedNumber = 0;
    
    while(shipsPlacedNumber < doubleDeckerNumberDefault) {
        
        addressLetter = (rand() % 10) + 'A';
        addressNumber = to_string(rand() % 10 + 1);
        
        fullAddress[0] = addressLetter + addressNumber;
        
        fullAddress[1] = createFinalShipAddress(fullAddress[0], doubleDecker);
        
        if(boardComputer.createDoubleDecker(fullAddress)) {
            
            shipsPlacedNumber++;
        }
        
        cout << fullAddress[0] << endl << fullAddress[1] << endl;
    }
}

void playerComputer::generateShipTD() {
    
    srand(time(NULL));
    
    string addressLetter;
    string addressNumber;
    
    string fullAddress[2];
    
    int shipsPlacedNumber = 0;
    
    while(shipsPlacedNumber < threeDeckerNumberDefault) {
        
        addressLetter = (rand() % 10) + 'A';
        addressNumber = to_string(rand() % 10 + 1);
        
        fullAddress[0] = addressLetter + addressNumber;
        
        fullAddress[1] = createFinalShipAddress(fullAddress[0], threeDecker);
        
        if(boardComputer.createThreeDecker(fullAddress)) {
            
            shipsPlacedNumber++;
        }
        
        cout << fullAddress[0] << endl << fullAddress[1] << endl;
    }
    
}

void playerComputer::generateShipFD() {
    
    srand(time(NULL));
    
    string addressLetter;
    string addressNumber;
    
    string fullAddress[2];
    
    int shipsPlacedNumber = 0;
    
    while(shipsPlacedNumber < fourDeckerNumberDefault) {
        
        addressLetter = (rand() % 10) + 'A';
        addressNumber = to_string(rand() % 10 + 1);
        
        fullAddress[0] = addressLetter + addressNumber;
        
        fullAddress[1] = createFinalShipAddress(fullAddress[0], fourDecker);
        
        if(boardComputer.createFourDecker(fullAddress)) {
            
            shipsPlacedNumber++;
        }
        
        cout << fullAddress[0] << endl << fullAddress[1] << endl;
    }
}

void playerComputer::prepareBoard() {
    
    generateShipSD();
    generateShipDD();
    generateShipTD();
    generateShipFD();
}

/////////////// creating second square's address based on the generated square's address

string createFinalShipAddress(string startAddress, squareType type) {
    
    string finalSquareAddress = startAddress;
    
    char proposition;
    bool finalAddressIsValid = false;
    
    while(!finalAddressIsValid) {
        
        int finalSquareDirection = (rand() % 4);
        
        if(finalSquareDirection == 0) { // up
            
            proposition = startAddress[1] - (type - 1);
            
            if(proposition > 48 && proposition < 58) {
                
                finalSquareAddress[1] = finalSquareAddress[1] - (type - 1);
                
                finalAddressIsValid = true;
            }
        }
        
        else if(finalSquareDirection == 1) { //right
            
            proposition = startAddress[0] + (type - 1);
            
            if(proposition >= 'A' && proposition <= 'J') {
                
                finalSquareAddress[0] = finalSquareAddress[0] + (type - 1);
                
                finalAddressIsValid = true;
            }
        }
        
        else if(finalSquareDirection == 2) { //down
            
            if(startAddress[1] < type + 7 && startAddress.length() < 3) {
                
                proposition = startAddress[1] + (type - 1);
                
                if(proposition > 48 && proposition < 58) {
                    
                    finalSquareAddress[1] = finalSquareAddress[1] + (type - 1);
                    
                    finalAddressIsValid = true;
                }
                
                else if(proposition == 58){
                    
                    finalSquareAddress = string(1, finalSquareAddress[0]) + "10";
                    
                    finalAddressIsValid = true;
                }
            }
        }
        
        else { // left
            
            proposition = startAddress[0] - (type - 1);
            
            if(proposition >='A' && proposition <= 'J') {
                
                finalSquareAddress[0] = finalSquareAddress[0] - (type - 1);
                
                finalAddressIsValid = true;
            }
        }
    }
    
    return finalSquareAddress;
}

/////////////// GAMEPLAY ////////////////

void playerComputer::stateMachine(board boardPlayer) {
    
    switch(state) {
            
        case previouslyNotHit:
            
            guess = previouslyNotHitGuess(boardPlayer);
            updateState();
            break;
            
        case hitOnce:
            
            guess = previouslyHitOnceGuess(boardPlayer);
            updateState();
            break;
            
        case hitMoreThanOnce:
            
            updateState();
            break;
            
            
        case mishit:
            
            updateState();
            break;
    }
}

string playerComputer::generateGuess(board boardPlayer) {
    
    stateMachine(boardPlayer);
    return guess;
}

void playerComputer::updateState() {
    
    if(lastTurnHit == false) {
        
        state = previouslyNotHit;
    }
    
    else {
        
        state = hitOnce;
    }
}

direction playerComputer::findShipDirection(string shipSquareCoords[2]) {
    
    direction shipDirection = horizontal;
    
    if(shipSquareCoords[0][0] == shipSquareCoords[1][0]) {
        
        shipDirection = vertical;
    }
    
    return shipDirection;
}

string playerComputer::previouslyNotHitGuess(board boardPlayer) {
    
    string finalGuess, addressLetter, addressNumber;
    
    addressLetter = (rand() % 10) + 'A';
    addressNumber = to_string(rand() % 10 + 1);
    
    finalGuess = addressLetter + addressNumber;
    
    return getFinalGuess(boardPlayer, finalGuess);
}


string playerComputer::getFinalGuess(board boardPlayer, string finalGuess) {
    
    if(!(boardPlayer.isGuessed(finalGuess))) {
        
        if(boardPlayer.isHit(finalGuess) == true) {
            
            lastTurnHit = true;
        }
        
        else {
            
            lastTurnHit = false;
        }
        
        lastTurnGuess = finalGuess;
        return finalGuess;
    }
    return 0;
}

//
//string playerComputer::previouslyHitGuess() {
//    
//    string finalGuess, addressLetter, addressNumber;
//    
//    if(hitAtLeastTwice == false) {
//        
//        previouslyHitOnceGuess();
//    }
//    
//    else {
//        
//        
//    }
//    
//    return finalGuess;
//}

string playerComputer::previouslyHitOnceGuess(board boardPlayer) {
    
    string finalGuess;
    char proposition;
    bool finalAddressIsValid = false;
    
    int finalSquareDirection = (rand() % 4);
    
    while(!finalAddressIsValid) {
    
        if(finalSquareDirection == 0) { // up
        
            proposition = lastTurnGuess[1] - 1;
        
            if(proposition > 48 && proposition < 58) {
            
                finalGuess[1] = finalGuess[1] - 1;
            
                finalAddressIsValid = true;
            }
        }
    
        else if(finalSquareDirection == 1) { //right
     
            proposition = lastTurnGuess[0] + 1;
        
            if(proposition >= 'A' && proposition <= 'J') {
            
                finalGuess[0] = finalGuess[0] + 1;
            
                finalAddressIsValid = true;
            }
        }
    
        else if(finalSquareDirection == 2) { //down
      
            if(lastTurnGuess.length() < 3) {
            
                proposition = lastTurnGuess[1] + 1;
            
                if(proposition > 48 && proposition < 58) {
                
                    finalGuess[1] = finalGuess[1] + 1;
                
                    finalAddressIsValid = true;
                }
            
                else if(proposition == 58){
                
                    finalGuess = string(1, finalGuess[0]) + "10";
                
                    finalAddressIsValid = true;
                }
            }

        }
    
        else { // left
       
            proposition = lastTurnGuess[0] - 1;
        
            if(proposition >= 'A' && proposition <= 'J') {
            
                finalGuess[0] = finalGuess[0] - 1;
            
                finalAddressIsValid = true;
            }
        }
    }
    return getFinalGuess(boardPlayer, finalGuess);
}

//  1 zgadnięty -->> losowanie, w którym kierunku zgadywać +++
//  więcej zgadnięte ->> który kieunek? zgadujemy w tym samym
//  jeśli ustalimy kierunek (2 trafione) ->> zgadujemy tylko w tym kierunku, juz nie po bokach
















