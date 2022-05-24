#pragma once

#ifndef PAWN_H
#define PAWN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Pawn : public Piece {    
public:
    Pawn(int col_, int row_, bool color_) : Piece(col_, row_, color_) {};

    virtual int getPieceCount() override { return 0; };

    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd) override;

    virtual int evaluate(const Board& bd) override;
};

#endif