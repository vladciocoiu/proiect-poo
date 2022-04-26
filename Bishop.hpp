#pragma once

#ifndef BISHOP_H
#define BISHOP_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Bishop : public Piece {    
public:
    std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif