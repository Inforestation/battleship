#include "square.hpp"

square::square() {
    
    this -> type = empty;
    this -> state = unknown;
}

square::square(squareType inType, squareState inState) {
    
    this -> type = inType;
    this -> state = inState;
}
