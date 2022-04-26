#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Knight : public Piece {
private:
    static const std::vector<std::pair<int, int>> OFFSETS;
    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif