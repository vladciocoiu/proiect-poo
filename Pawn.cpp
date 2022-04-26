#include <vector>
#include "Pawn.hpp"
#include "Board.hpp"
#include "King.hpp"

std::vector<Move> Pawn::generatePseudoLegalMoves(const Board& bd) {   
    auto [row, col] = getSquare();

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());


    // TODO: code en passant

    // white pawns move to bigger rows, and black pawns to smaller ones
    static const int ROW_OFFSET = (getColor() ? 1 : -1);

    // needed for the 2 square move (pawns can only move 2 squares from their initial row)
    static const int STARTING_ROW = (getColor() ? 1 : 6);

    // the row where the pawn can promote
    // static const int PROMOTION_ROW = (getColor() ? 7 : 0);

    // normal 1 square move
    if(row + ROW_OFFSET >= 0 && row + ROW_OFFSET < 8 && !occupiedSquares.count({row + ROW_OFFSET, col})) {
        moves.push_back(Move{col, row, col, row + ROW_OFFSET, getColor(), false, false, false, false, ""});

        // 2 square move
        // can be possible only if normal move is possible
        if(row == STARTING_ROW && row + 2 * ROW_OFFSET >= 0 
        && row + 2 * ROW_OFFSET < 8 && !occupiedSquares.count({row + ROW_OFFSET, col})) {
            moves.push_back(Move{col, row, col, row + 2 * ROW_OFFSET, getColor(), false, false, false, false, ""});
        }
    }

    return moves;
}
