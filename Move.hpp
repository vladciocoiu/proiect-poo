#pragma once

#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
private:
    int colFrom, rowFrom, colTo, rowTo;
    bool color, capture, enPassant, castle, promotion;
    std::string promotionPiece; // empty string if not promotion, otherwise one of "bishop", "knight", "rook", "queen"
public:

    // getters and setters
    bool isPromotion() const { return promotion; }
    std::string getPromotionPiece() const { return promotionPiece; }
    int getRowTo() const { return rowTo; }
    int getColTo() const { return colTo; }
    int getRowFrom() const { return rowFrom; }
    int getColFrom() const { return colFrom; }
    bool isEnPassant() const { return enPassant; }
    bool isCapture() const { return capture; }
    bool isCastle() const { return castle; }
    bool getColor() const { return color; }


    // constructor de initializare
    Move(int colFrom_, int rowFrom_, int colTo_, int rowTo_, 
         bool color_, bool capture_, bool enPassant_, bool castle_, bool promotion_, 
         const std::string& promotionPiece_);

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, Move& mv);
};

#endif