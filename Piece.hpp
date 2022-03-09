#pragma once

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "Move.hpp"
// #include "Board.hpp"
class Board;

class Piece {
private:
    std::string type; // "pawn", "knight", "bishop", "rook", "queen", or "king"
    char col, row; // 0 - 7
    bool color; // 0 for black, 1 for white
public:

    // getters and setters
    bool getColor() { return color; }
    std::pair<char, char> getSquare() { return {row, col}; }

    // constructor de initializare
    Piece(const std::string& type_, char col_, char row_, bool color_);

    // constructor de copiere
    Piece(const Piece& other);

    // operator =
    Piece& operator=(const Piece& other);

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Piece& pc);


    // destructor 
    ~Piece();

    // generates all pseudo-legal moves
    // (doesn't care about leaving the king in check)
    // only implemented for knights now, will probably make separate classes for each piece type later
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);

    // method for making a move
    // still have to make en passant, captures and castles
    // SHOULD ONLY HAVE LEGAL MOVES AS ARGUMENTS
    void makeMove(const Move& m);

};

#endif