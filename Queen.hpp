#pragma once

#ifndef QUEEN_H
#define QUEEN_H

#include <vector>

#include "Piece.hpp"
#include "King.hpp"

class Queen : public Piece {    
public:
    Queen(int col_, int row_, bool color_);
    
    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif