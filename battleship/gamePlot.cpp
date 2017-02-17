#include "gamePlot.hpp"
#include <unistd.h>

void introduction();
board createBoard();

/////////////// gamePlot constructor

gamePlot::gamePlot() {
    
    computer = playerComputer();
    
    state = initialization;
    playState = playerTurn;
    
    stateMachine();
}

/////////////// moderating phases of the game's plot

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

/////////////// PHASE 1: introduction


void introduction() {
    
    cout << "Battleship" << endl << endl;
    usleep(1000000);
    cout << "Welcome to Battleship. Type 'start' to begin." << endl << endl;
    
    string startingCommand = "";
    
    while(startingCommand != "start") {
        
        cin >> startingCommand;
    }
}

/////////////// PHASE 2: creating player's and computer's board

board createBoard() {
    
    board gameBoard;
    
    string coords[2];
    
    cout << endl << "Setting single deckers" << endl;
    usleep(1000000);
    
    while(gameBoard.singleDeckerNumber != (gameBoard.singleDeckerIndex)) {
        
        cout << (gameBoard.singleDeckerNumber - gameBoard.singleDeckerIndex) << " to go" << endl;
        usleep(1000000);
        cout << "Please type in single decker's address" << endl;
        
        cin >> coords[0];
        
        gameBoard.createSingleDecker(coords[0]);
        
        cout << endl << endl;
        usleep(1000000);
        
        gameBoard.showBoard(true);
    }
    
    cout << endl << "Setting double deckers" << endl;
    usleep(1000000);
    
    while(gameBoard.doubleDeckerNumber != (gameBoard.doubleDeckerIndex)) {
        
        cout << (gameBoard.doubleDeckerNumber - gameBoard.doubleDeckerIndex) << " to go" << endl;
        usleep(1000000);
        
        cout << "Please type in double decker's opening address" << endl;
        cin >> coords[0];
        
        cout << "Please type in double decker's closing address" << endl;
        cin >> coords[1];
        
        gameBoard.createDoubleDecker(coords);
        
        cout << endl << endl;
        
        gameBoard.showBoard(true);
    }
    
    cout << endl << "Setting three deckers" << endl;
    usleep(1000000);
    
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
    usleep(1000000);
    
    while(gameBoard.fourDeckerNumber != (gameBoard.fourDeckerIndex)) {
        
        cout << (gameBoard.fourDeckerNumber - gameBoard.fourDeckerIndex) << " to go" << endl;
        usleep(1000000);
        
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
    
    computer.prepareBoard();
    
   // computer.boardComputer.showBoard(true);
}

/////////////// PHASE 3: the game

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

// PLAYER'S TURN

void gamePlot::turnPlayer() {
    
    usleep(1000000);
    cout << endl << endl << "PLAYER'S TURN" << endl << endl;
    usleep(1000000);
    cout << "Computer's board" << endl << endl;
    usleep(1000000);
    computer.boardComputer.showBoard(false);
    usleep(1000000);
    cout << "Guess." << endl;
    
    string guessPlayer;
    
    cin >> guessPlayer;
    cout << endl;
    
    guessResult result = computer.boardComputer.hitSquare(guessPlayer);
    
    if(result == hit) {
        
        usleep(1000000);
        cout << "Hit!" << endl << endl;
    }
    
    else if(result == sunk) {
        
        usleep(1000000);
        cout << "Hit and sunk!" << endl << endl;
        
        if(computer.boardComputer.hasGameEnded()) {
            
            usleep(1000000);
            cout << "Player wins!" << endl << endl;
            
            playState = gameplayEnd;
        }
    }
    
    else {
        
        usleep(1000000);
        cout << "Miss!" << endl << endl;
        
        playState = computerTurn;
    }
    
    cout << "Computer's board" << endl << endl;
    
    usleep(1000000);
    
    computer.boardComputer.showBoard(false);
}



// COMPUTER'S TURN

void gamePlot::turnComputer() {
    
    string guess = computer.generateGuess(boardPlayer);
    guessResult result = boardPlayer.hitSquare(guess);
    
    usleep(1000000);
    cout << endl << endl << "COMPUTER'S TURN" << endl << endl;
    
    usleep(1000000);
    cout << "Player's board" << endl << endl;
    
    usleep(1000000);
    cout << "Guessing... " << guess << endl << endl;
    
    if(result == hit) {
        
        usleep(1000000);
        cout << "Hit!" << endl << endl;
        computer.hitCounter++;
    }
    
    else if(result == sunk) {
        
        usleep(1000000);
        cout << "Hit and sunk!" << endl << endl;
        computer.hitCounter = 0;
        
        if(boardPlayer.hasGameEnded()) {
            
            usleep(1000000);
            cout << "Computer wins!" << endl << endl;
            
            playState = gameplayEnd;
        }
    }
    
    else {
        
        usleep(1000000);
        cout << "Miss!" << endl << endl;
        
        computer.hitCounter = 0;
        
        playState = playerTurn;
        
    }
    
    usleep(1000000);
    cout << "Player's board" << endl << endl;
    
    usleep(1000000);
    
    boardPlayer.showBoard(false);
}











