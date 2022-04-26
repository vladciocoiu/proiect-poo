#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>

#include "Piece.hpp"

class Board;

class Knight : public Piece {
private:
    static const std::vector<std::pair<int, int>> OFFSETS;
    
public:
    Knight(int col_, int row_, bool color_);
    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif