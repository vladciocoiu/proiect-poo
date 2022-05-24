#pragma once

#ifndef QUEEN_H
#define QUEEN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Queen : public Piece {    
public:
    Queen(int col_, int row_, bool color_) : Piece(col_, row_, color_) {};

    virtual int getPieceCount() override { return 9; };
    
    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd) override;

    virtual int evaluate(const Board& bd) override;
};

#endif