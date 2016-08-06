#include <iostream>

//#ifndef square_hpp
//#define square_hpp
//#include "square.hpp"
//#endif /* square_hpp */
//
//#ifndef ship_hpp
//#define ship_hpp
//#include "ship.hpp"
//#endif /* ship_hpp */

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

//#ifndef playerComputer_hpp
//#define playerComputer_hpp
//#include "playerComputer.hpp"
//#endif /* playerComputer_hpp */

using namespace std;

int main() {
    
    board gameBoard;
    
//    gameBoard.createSingleDecker("C8");
    
//    string coords[2] = {"A2", "B2"};
//    gameBoard.createDoubleDecker(coords);
    
//    string coords2[2] = {"A1", "A3"};
//    gameBoard.createDoubleDecker(coords2);
    
    string coords3[3] = {"B2", "B4"};
    gameBoard.createThreeDecker(coords3);
    
    gameBoard.showBoard();
    
    return 0;
}
