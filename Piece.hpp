#pragma once

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <memory>

#include "Move.hpp"

class Board;
class King;

class Piece {
private:
    int col, row; // 0 - 7
    bool color; // 0 for black, 1 for white
protected:
    Piece(const Piece&) = default;
    Piece& operator=(const Piece&) = default;
public:

    // getters and setters
    virtual std::string getPieceType() = 0;
    bool getColor() const { return color; }
    std::pair<int, int> getSquare() const { return {row, col}; }
    void setSquare(std::pair<int, int> sq) { row = sq.first, col = sq.second; };

    virtual int getPieceCount() = 0;

    // constructor de initializare
    Piece(int col_, int row_, bool color_);

    virtual std::shared_ptr<Piece> clone() const = 0;


    // operator <<
    friend std::ostream& operator<<(std::ostream& os, Piece& pc);


    // destructor 
    virtual ~Piece() {}

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd) = 0;

    virtual int evaluate(const Board& bd) = 0;

    // legal moves are all moves that are pseudo legal and don't put the friendly king in check
    std::vector<Move> generateLegalMoves(Board bd);

};

#endif