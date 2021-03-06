#include <vector>
#include <algorithm>
#include <array>

#include "Pawn.hpp"
#include "Board.hpp"
#include "King.hpp"

std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}

std::vector<Move> Pawn::generatePseudoLegalMoves(const Board& bd) {   
    int currRow = getSquare().first;
    int currCol = getSquare().second;

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());

    const std::array<std::string, 4> PROMOTION_PIECES = {"knight", "bishop", "rook", "queen"};


    // white pawns move to bigger rows, and black pawns to smaller ones
    const int ROW_OFFSET = (getColor() ? 1 : -1);

    // needed for the 2 square move (pawns can only move 2 squares from their initial row)
    const int STARTING_ROW = (getColor() ? 1 : 6);

    // the row where the pawn can promote
    const int PROMOTION_ROW = (getColor() ? 7 : 0);

    // en passant
    if(bd.getEnPassantCol() != -1 && (bd.getEnPassantCol() - currCol) == 1 && currRow == (getColor() ? 4 : 3)) {
        if(currRow + ROW_OFFSET == PROMOTION_ROW) {
            std::transform(PROMOTION_PIECES.begin(), PROMOTION_PIECES.end(), moves.begin(), [bd, this, currRow, currCol, ROW_OFFSET](std::string promotionPiece) {
                return Move{currCol, currRow, bd.getEnPassantCol(), currRow + ROW_OFFSET, getColor(), true, true, false, true, promotionPiece};
            });
        } else {
            moves.push_back(Move{currCol, currRow, bd.getEnPassantCol(), currRow + ROW_OFFSET, getColor(), true, true, false, false, ""});
        }
    }

    // normal 1 square move
    if(currRow + ROW_OFFSET >= 0 && currRow + ROW_OFFSET < 8 
    && !occupiedSquares.contains({currRow + ROW_OFFSET, currCol})
    && !enemySquares.contains({currRow + ROW_OFFSET, currCol})) {
        if(currRow + ROW_OFFSET == PROMOTION_ROW) {
            std::transform(PROMOTION_PIECES.begin(), PROMOTION_PIECES.end(), moves.begin(), [this, currRow, currCol, ROW_OFFSET](std::string promotionPiece) {
                return Move{currCol, currRow, currCol, currRow + ROW_OFFSET, getColor(), false, false, false, true, promotionPiece};

            });
        } else {
            moves.push_back(Move{currCol, currRow, currCol, currRow + ROW_OFFSET, getColor(), false, false, false, false, ""});
        }

        // 2 square move
        // can be possible only if normal move is possible
        if(currRow == STARTING_ROW 
        && !occupiedSquares.contains({currRow + 2 * ROW_OFFSET, currCol})
        && !enemySquares.contains({currRow + 2 * ROW_OFFSET, currCol})) {
            moves.push_back(Move{currCol, currRow, currCol, currRow + 2 * ROW_OFFSET, getColor(), false, false, false, false, ""});
        }
    }

    // capture moves
    for(int nextCol: {currCol - 1, currCol + 1}) {
        if(nextCol < 0 || nextCol >= 8) continue;
        if(enemySquares.contains({currRow + ROW_OFFSET, nextCol})) {
            if(currRow + ROW_OFFSET == PROMOTION_ROW) {
                std::transform(PROMOTION_PIECES.begin(), PROMOTION_PIECES.end(), moves.begin(), [this, currRow, currCol, nextCol, ROW_OFFSET](std::string promotionPiece) {
                    return Move{currCol, currRow, nextCol, currRow + ROW_OFFSET, getColor(), true, false, false, true, promotionPiece};
                });
            } else {
                moves.push_back(Move{currCol, currRow, nextCol, currRow + ROW_OFFSET, getColor(), true, false, false, false, ""});
            }
        }
    }

    return moves;
}

int Pawn::evaluate(const Board& /*bd*/) {
    return 100; 
}
