#pragma once

#ifndef KING_H
#define KING_H

#include <vector>

// #include "Board.hpp"
#include "Piece.hpp"

class Board;

class King : public Piece {
private:
    static const std::vector<std::pair<int, int>> OFFSETS;
public:
    King(int col_, int row_, bool color_);

    virtual int getPieceCount() override { return 0; };

    std::shared_ptr<Piece> clone() const override;

    virtual std::vector<Move> generatePseudoLegalMoves(const Board& bd) override;

    bool isInCheck(const Board& bd) const;

    virtual int evaluate(const Board& bd) override;
};

#endif