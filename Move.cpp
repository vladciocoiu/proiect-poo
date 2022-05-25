#include "Move.hpp"
#include "Errors.hpp"

#include <iostream>


// constructor de initializare
Move::Move(int colFrom_, int rowFrom_, int colTo_, int rowTo_, 
        bool color_, bool capture_, bool enPassant_, bool castle_, bool promotion_, 
        const std::string& promotionPiece_) 
: colFrom{colFrom_}, rowFrom{rowFrom_}, colTo{colTo_}, rowTo{rowTo_}, 
    color{color_}, capture{capture_}, enPassant{enPassant_}, castle{castle_}, promotion{promotion_}, 
    promotionPiece{promotionPiece_} {

    if(colFrom_ < 0 || colFrom_ >= 8 || rowFrom_ < 0 || rowFrom_ >= 8 
    || colTo_ < 0 || colTo_ >= 8 || rowTo_ < 0 || rowTo_ >= 8) {
        throw move_error{"Move coordinates out of bounds."};
    }
}

// operator <<
std::ostream& operator<<(std::ostream& os, Move& mv) {
    os << (char)(mv.getColFrom() + 'a') << (char)(mv.getRowFrom() + '1') 
       << (char)(mv.getColTo() + 'a') << (char)(mv.getRowTo() + '1') 
       << (mv.getPromotionPiece().length() ? mv.getPromotionPiece()[0] : ' ');

    return os;
}
