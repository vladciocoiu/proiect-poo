#pragma once

#ifndef KING_H
#define KING_H

#include <vector>

#include "Board.hpp"
#include "Piece.hpp"

class Board;

class King : public Piece {
private:
    static const std::vector<std::pair<int, int>> OFFSETS;
    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);

    bool isInCheck(const Board& bd) const;
};

#endif