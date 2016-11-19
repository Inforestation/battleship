#include "gamePlot.hpp"

void introduction();
board createBoard();

gamePlot::gamePlot() {
    
    computer = playerComputer();
    
    state = initialization;
    playState = playerTurn;
    
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
            
            createBoardPlayer();
            state = creatingBoardComputer;
            stateMachine();
            break;
            
        case creatingBoardComputer:
            
            createBoardComputer();
            state = play;
            stateMachine();
            break;
            
        case play:
            
            playGame();
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

board createBoard() {
    
    board gameBoard;
    
    string coords[2];
    
    cout << endl << "Setting single deckers" << endl;
    
    while(gameBoard.singleDeckerNumber != (gameBoard.singleDeckerIndex)) {
        
        cout << (gameBoard.singleDeckerNumber - gameBoard.singleDeckerIndex) << " to go" << endl;
        cout << "Please type in single decker's address" << endl;
        
        cin >> coords[0];
        
        gameBoard.createSingleDecker(coords[0]);
        
        cout << endl << endl;
        
        gameBoard.showBoard(true);
    }
    
    cout << endl << "Setting double deckers" << endl;
    
    while(gameBoard.doubleDeckerNumber != (gameBoard.doubleDeckerIndex)) {
        
        cout << (gameBoard.doubleDeckerNumber - gameBoard.doubleDeckerIndex) << " to go" << endl;
        
        cout << "Please type in double decker's opening address" << endl;
        cin >> coords[0];
        
        cout << "Please type in double decker's closing address" << endl;
        cin >> coords[1];
        
        gameBoard.createDoubleDecker(coords);
        
        cout << endl << endl;
        
        gameBoard.showBoard(true);
    }
    
    cout << endl << "Setting three deckers" << endl;
    
    while(gameBoard.threeDeckerNumber != (gameBoard.threeDeckerIndex)) {
        
        cout << (gameBoard.threeDeckerNumber - gameBoard.threeDeckerIndex) << " to go" << endl;
        
        cout << "Please type in three decker's opening address" << endl;
        cin >> coords[0];
        
        cout << "Please type in three decker's closing address" << endl;
        cin >> coords[1];
        
        gameBoard.createThreeDecker(coords);
        
        cout << endl << endl;
        
        gameBoard.showBoard(true);
    }
    
    cout << endl << "Setting four deckers" << endl;
    
    while(gameBoard.fourDeckerNumber != (gameBoard.fourDeckerIndex)) {
        
        cout << (gameBoard.fourDeckerNumber - gameBoard.fourDeckerIndex) << " to go" << endl;
        
        cout << "Please type in four decker's opening address" << endl;
        cin >> coords[0];
        
        cout << "Please type in four decker's closing address" << endl;
        cin >> coords[1];
        
        gameBoard.createFourDecker(coords);
        
        cout << endl << endl;
        
        gameBoard.showBoard(true);
    }
    
    return gameBoard;
}

void gamePlot::createBoardPlayer() {
    
    boardPlayer = createBoard();
}

void gamePlot::createBoardComputer() {
    
    boardComputer = createBoard();
}

void gamePlot::playGame() {
    
    switch (playState) {
            
        case playerTurn:
            
            turnPlayer();
            playGame();
            break;
            
        case computerTurn:
            
            turnComputer();
            playGame();
            break;
            
        case gameplayEnd:
            
            break;
            
        default:
            break;
    }
}

// PLAYER'S TURN!

void gamePlot::turnPlayer() {
    
    cout << endl << endl << "PLAYER'S TURN" << endl << endl;
    
    cout << "Computer's board" << endl << endl;
    
    boardComputer.showBoard(false);
    
    cout << "Guess." << endl;
    
    string guess;
    
    cin >> guess;
    cout << endl;
    
    guessResult result = boardComputer.hitSquare(guess);

    if(result == hit) {
        
        cout << "Hit!" << endl << endl;
    }
    
    else if(result == sunk) {
        
        cout << "Hit and sunk!" << endl << endl;
        
        if(boardComputer.hasGameEnded()) { 
            
            cout << "Player wins!" << endl << endl;
            
             playState = gameplayEnd;
        }
    }
    
    else {
        
        cout << "Miss!" << endl << endl;
        
        playState = computerTurn;
    }
    
    cout << "Computer's board" << endl << endl;
    
    boardComputer.showBoard(false);
}

// COMPUTER'S TURN!

void gamePlot::turnComputer() {

    cout << endl << endl << "COMPUTER'S TURN" << endl << endl;
    
    cout << "Player's board" << endl << endl;
    
    boardPlayer.showBoard(false);

    cout << "Guess." << endl;

    string guess;

    cin >> guess;
    cout << endl;
    
    guessResult result = boardPlayer.hitSquare(guess);

    if(result == hit) {
    
        cout << "Hit!" << endl << endl;
    }
    
    else if(result == sunk) {
    
        cout << "Hit and sunk!" << endl << endl;
        
        if(boardPlayer.hasGameEnded()) {
            
            cout << "Computer wins!" << endl << endl;
            
            playState = gameplayEnd;
        }
    }

    else {
    
        cout << "Miss!" << endl << endl;
    
        playState = playerTurn;
    }

    cout << "Player's board" << endl << endl;
    
    boardPlayer.showBoard(false);
}











