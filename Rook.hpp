#pragma once

#ifndef ROOK_H
#define ROOK_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Rook : public Piece {    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif