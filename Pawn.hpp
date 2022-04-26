#pragma once

#ifndef PAWN_H
#define PAWN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Pawn : public Piece {    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif