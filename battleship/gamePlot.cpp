#include "gamePlot.hpp"

void introduction();

gamePlot::gamePlot() {
    
    state = initialization;
    
    stateMachine();
}

void gamePlot::stateMachine() {
    
    switch(state) {
            
        case initialization:
            
            introduction();
            state = creatingBoardPlayer;
            stateMachine();
            break;
            
        case creatingBoardPlayer:
            
            state = creatingBoardComputer;
            stateMachine();
            break;
            
        case creatingBoardComputer:
            
            state = play;
            stateMachine();
            break;
            
        case play:
            
            state = gameEnd;
            stateMachine();
            break;
            
        case gameEnd:
            
            break;
            
        default:
            break;
    }
}

void introduction() {
    
    cout << "Battleship" << endl << endl;
    cout << "Welcome to Battleship. Type 'start' to begin." << endl << endl;
    
    string startingCommand = "";
    
    while(startingCommand != "start") {
        
        cin >> startingCommand;
    }
}

board createBoardPlayer(board boardPlayer) {
    
    string coords[2];
    
    cout << endl << "Setting single deckers" << endl;
    
    for(int a = 0; a <= singleDeckerNumber; a++) {
        
        cout << (singleDeckerNumber - singleDeckerIndex) << "to go" << endl;
        cout << "Please type in single decker's address" << endl;
        
        cin >> coords[0];
        
        boardPlayer.createSingleDecker(coords[0]);
    }
    
    return boardPlayer;
}













