#include "Move.hpp"
#include <iostream>


// constructor de initializare
Move::Move(char colFrom_, char rowFrom_, char colTo_, char rowTo_, 
        bool color_, bool capture_, bool enPassant_, bool castle_, bool promotion_, 
        const std::string& promotionPiece_) 
: colFrom(colFrom_), rowFrom(rowFrom_), colTo(colTo_), rowTo(rowTo_), 
    color(color_), capture(capture_), enPassant(enPassant_), castle(castle_), promotion(promotion_), 
    promotionPiece(promotionPiece_) {
    std::cout << "Init Move\n";
}

// operator <<
std::ostream& operator<<(std::ostream& os, const Move& mv) {
    os << "Move from square  (" << mv.getRowFrom() << ", " << mv.getColFrom() <<  ") to (" 
                            << mv.getRowTo() << ", " << mv.getColTo() << ")\n";
    return os;
}
