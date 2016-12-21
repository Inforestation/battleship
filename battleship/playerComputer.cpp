#include "playerComputer.hpp"
using namespace std;

string createFinalShipAddress(string startAddress, squareType type);

playerComputer::playerComputer() {}

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















