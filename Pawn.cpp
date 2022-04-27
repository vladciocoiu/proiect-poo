#include <vector>
#include "Pawn.hpp"
#include "Board.hpp"
#include "King.hpp"

Pawn::Pawn(int col_, int row_, bool color_) 
: Piece(col_, row_, color_) {
    std::cout << "Init Pawn\n";
}

std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}

std::vector<Move> Pawn::generatePseudoLegalMoves(const Board& bd) {   
    auto [currRow, currCol] = getSquare();

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());


    // white pawns move to bigger rows, and black pawns to smaller ones
    static const int ROW_OFFSET = (getColor() ? 1 : -1);

    // needed for the 2 square move (pawns can only move 2 squares from their initial row)
    static const int STARTING_ROW = (getColor() ? 1 : 6);

    // the row where the pawn can promote
    static const int PROMOTION_ROW = (getColor() ? 7 : 0);

    // en passant
    if(abs(bd.getEnPassantCol() - currCol) == 1 && currRow == (getColor() ? 4 : 3)) {
        if(currRow + ROW_OFFSET == PROMOTION_ROW) {
            for(const std::string promotionPiece: {"knight", "bishop", "rook", "queen"}) {
                moves.push_back(Move{currCol, currRow, bd.getEnPassantCol(), currRow + ROW_OFFSET, getColor(), true, true, false, true, promotionPiece});
            }
        } else {
            moves.push_back(Move{currCol, currRow, bd.getEnPassantCol(), currRow + ROW_OFFSET, getColor(), true, true, false, false, ""});
        }
    }

    // normal 1 square move
    if(currRow + ROW_OFFSET >= 0 && currRow + ROW_OFFSET < 8 
    && !occupiedSquares.count({currRow + ROW_OFFSET, currCol})
    && !enemySquares.count({currRow + ROW_OFFSET, currCol})) {
        if(currRow + ROW_OFFSET == PROMOTION_ROW) {
            for(const std::string promotionPiece: {"knight", "bishop", "rook", "queen"}) {
                moves.push_back(Move{currCol, currRow, currCol, currRow + ROW_OFFSET, getColor(), false, false, false, true, promotionPiece});
            } 
        } else {
            moves.push_back(Move{currCol, currRow, currCol, currRow + ROW_OFFSET, getColor(), false, false, false, false, ""});
        }

        // 2 square move
        // can be possible only if normal move is possible
        if(currRow == STARTING_ROW 
        && !occupiedSquares.count({currRow + 2 * ROW_OFFSET, currCol})
        && !enemySquares.count({currRow + 2 * ROW_OFFSET, currCol})) {
            moves.push_back(Move{currCol, currRow, currCol, currRow + 2 * ROW_OFFSET, getColor(), false, false, false, false, ""});
        }
    }

    // capture moves
    for(int nextCol: {currCol - 1, currCol + 1}) {
        if(nextCol < 0 || nextCol >= 8) continue;
        if(enemySquares.count({currRow + ROW_OFFSET, nextCol})) {
            if(currRow + ROW_OFFSET == PROMOTION_ROW) {
                for(const std::string promotionPiece: {"knight", "bishop", "rook", "queen"}) {
                    moves.push_back(Move{currCol, currRow, nextCol, currRow + ROW_OFFSET, getColor(), true, false, false, true, promotionPiece});
                }
            } else {
                moves.push_back(Move{currCol, currRow, nextCol, currRow + ROW_OFFSET, getColor(), true, false, false, false, ""});
            }
        }
    }

    return moves;
}
