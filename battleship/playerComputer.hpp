#ifndef playerComputer_hpp
#define playerComputer_hpp
#endif /* playerComputer_hpp */

#ifndef board_hpp
#define board_hpp
#include "board.hpp"
#endif /* board_hpp */

#include <stdio.h>
#include <string>
using namespace std;

class playerComputer {
    
public:
    
    string *SDAddresses;
    string **DDAddresses;
    string **TDAddresses;
    string **FDAddresses;

    string generateShipSD();
    string generateShipDD();
    string generateShipTD();
    string generateShipFD();
    
    playerComputer();
};