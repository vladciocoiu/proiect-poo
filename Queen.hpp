#pragma once

#ifndef QUEEN_H
#define QUEEN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Queen : public Piece {    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif