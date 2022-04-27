#pragma once

#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include <memory>

#include "Piece.hpp"

class Board;

class Knight : public Piece {
private:
    static const std::vector<std::pair<int, int>> OFFSETS;
    
public:
    Knight(int col_, int row_, bool color_);
    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd);
};

#endif