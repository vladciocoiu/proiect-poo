#include <vector>
#include "Knight.hpp"
#include "Board.hpp"

const std::vector<std::pair<int, int>> Knight::OFFSETS = {
    {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
    {2, 1}, {-2, 1}, {2, -1}, {-2, -1}
};

std::shared_ptr<Piece> Knight::clone() const {
    return std::make_shared<Knight>(*this);
}


std::vector<Move> Knight::generatePseudoLegalMoves(const Board& bd) {   
    auto [currRow, currCol] = getSquare();

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());


    for (auto [rowOffset, colOffset]: OFFSETS) {
        int newRow = currRow + rowOffset;
        int newCol = currCol + colOffset;

        // move is out of bounds, so we skip it
        if(newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) continue;

        // if a friendly piece is on that square, we cannot make the move
        if(occupiedSquares.contains({newRow, newCol})) continue;

        // make a new move that isn't a capture / castle / en passant / promotion
        // with the corresponding squares and color
        moves.push_back(Move{currCol, currRow, newCol, newRow, getColor(), enemySquares.contains({ newRow, newCol }), false, false, false, ""});
    }

    return moves;
}

int Knight::evaluate(const Board& /*bd*/) {
    return 300; 
}
