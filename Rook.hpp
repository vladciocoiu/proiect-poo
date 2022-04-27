#pragma once

#ifndef ROOK_H
#define ROOK_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Rook : public Piece {    
public:
    Rook(int col_, int row_, bool color_);

    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif