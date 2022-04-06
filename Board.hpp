#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Piece.hpp"

class Board {
private:
    std::vector<Piece> pieces;
public:

    // constructor de initializare
    Board(const std::vector<Piece>& pieces_ = {});

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Board& bd);

    // add a piece to the pieces vector
    void addPiece(const Piece& pc);

    // method that returns a list of occupied squares 
    // needed for move generation
    std::set<std::pair<int, int>> getOccupiedSquares(bool color) const;
};

#endif