#include <vector>
#include "King.hpp"
#include "Board.hpp"

const std::vector<std::pair<int, int>> King::OFFSETS = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

std::vector<Move> King::generatePseudoLegalMoves(const Board& bd) {   
    auto [row, col] = getSquare();

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());


    for (auto [rowOffset, colOffset]: OFFSETS) {
        int newRow = row + rowOffset;
        int newCol = col + colOffset;

        // move is out of bounds, so we skip it
        if(newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) continue;

        // if a friendly piece is on that square, we cannot make the move
        if(occupiedSquares.count({newRow, newCol})) continue;

        // make a new move that isn't a capture / castle / en passant / promotion
        // with the corresponding squares and color
        moves.push_back(Move{col, row, newCol, newRow, getColor(), false, false, false, false, ""});
    }

    return moves;
}

// TODO: code this function that checks if the king is in check
bool King::isInCheck(const Board& bd) const {
    return getSquare().first < 3;
}
