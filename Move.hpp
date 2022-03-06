#pragma once

#ifndef MOVE_H
#define MOVE_H


class Move {
private:
    char colFrom, rowFrom, colTo, rowTo;
    bool color, capture, enPassant, castle, promotion;
    std::string promotionPiece; // empty string if not promotion, otherwise one of "bishop", "knight", "rook", "queen"
public:

    // getters and setters
    bool isPromotion() { return promotion; }
    std::string getPromotionPiece() { return promotionPiece; }
    char getRowTo() { return rowTo; }
    char getColTo() { return colTo; }

    // constructor de initializare
    Move(char colFrom_, char rowFrom_, char colTo_, char rowTo_, 
         bool color_, bool capture_, bool enPassant_, bool castle_, bool promotion_, 
         const std::string& promotionPiece_) 
    : colFrom(colFrom_), rowFrom(rowFrom_), colTo(colTo_), rowTo(rowTo_), 
      color(color_), capture(capture_), enPassant(enPassant_), castle(castle_), promotion(promotion_), 
      promotionPiece(promotionPiece_) {
        std::cout << "Init Move\n";
    }

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Move& mv) {
        os << "Move from square  (" << mv.rowFrom << ", " << mv.colFrom <<  ") to (" 
                                << mv.rowTo << ", " << mv.colTo << ")" << "\n";
        return os;
    }
};

#endif