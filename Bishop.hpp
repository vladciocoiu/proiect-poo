#pragma once

#ifndef BISHOP_H
#define BISHOP_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Bishop : public Piece {    
public:
    Bishop(int col_, int row_, bool color_);

    virtual int getPieceCount() override { return 3; };

    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd) override;

    virtual int evaluate(const Board& bd) override;
};

#endif