#pragma once

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "Move.hpp"
// #include "Board.hpp"
// #include "King.hpp"

// #include "Board.hpp"
class Board;
class King;

class Piece {
private:
    int col, row; // 0 - 7
    bool color; // 0 for black, 1 for white
public:

    // getters and setters
    bool getColor() const { return color; }
    std::pair<int, int> getSquare() const { return {row, col}; }

    // constructor de initializare
    Piece(int col_, int row_, bool color_);

    // constructor de copiere
    Piece(const Piece& other);

    // operator =
    Piece& operator=(const Piece& other);

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Piece& pc);


    // destructor 
    virtual ~Piece();

    // legal moves are all moves that are pseudo legal and don't put the friendly king in check
    std::vector<Move> generateLegalMoves(const King& friendlyKing, std::vector<Move> pseudoLegalMoves, const Board& bd);

    // method for making a move
    // still have to make en passant, captures and castles
    // SHOULD ONLY HAVE PSEUDO LEGAL MOVES AS ARGUMENTS
    void makeMove(const Move& m);

    void unmakeMove(const Move& m);

};

#endif