#pragma once

#ifndef PAWN_H
#define PAWN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Pawn : public Piece {    
public:
    Pawn(int col_, int row_, bool color_);

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif