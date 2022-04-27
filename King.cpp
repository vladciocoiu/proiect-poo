#include <vector>
#include "King.hpp"
#include "Board.hpp"

const std::vector<std::pair<int, int>> King::OFFSETS = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

King::King(int col_, int row_, bool color_) 
: Piece(col_, row_, color_) {
    std::cout << "Init King\n";
}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this);
}

std::vector<Move> King::generatePseudoLegalMoves(const Board& bd) {   
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
        if(occupiedSquares.count({newRow, newCol})) continue;

        // make a new move that isn't a capture / castle / en passant / promotion
        // with the corresponding squares and color
        moves.push_back(Move{currCol, currRow, newCol, newRow, getColor(), (bool)enemySquares.count({ newRow, newCol }), false, false, false, ""});
    }

    // castle moves
    int castleShortBit = (getColor() ? 0 : 2);
    int castleLongBit = (getColor() ? 1 : 3);

    // no pieces should be between the rook and king

    // short castle (e1g1 / e8g8)
    if(bd.getCastleRights() && castleShortBit) {
        bool ok = true;
        for(int c = 5; c <= 6; c++) {
            if(occupiedSquares.count({currRow, c}) || enemySquares.count({currRow, c})) {
                ok = false;
            }
        }
        if(ok) moves.push_back(Move{currCol, currRow, currCol + 2, currRow, getColor(), false, false, true, false, ""});
    }

    // long castle (e1c1 / e8c8)
    if(bd.getCastleRights() && castleLongBit) {
        bool ok = true;
        for(int c = 1; c <= 3; c++) {
            if(occupiedSquares.count({currRow, c}) || enemySquares.count({currRow, c})) {
                ok = false;
            }        
        }
        if(ok) moves.push_back(Move{currCol, currRow, currCol - 2, currRow, getColor(), false, false, true, false, ""}); 
    }

    return moves;
}

bool King::isInCheck(const Board& bd) const {
    auto pieces = bd.getPieces();
    for(auto piece: pieces) {
        if(piece->getColor() != getColor()) {
            auto moves = piece->generatePseudoLegalMoves(bd);
            for (auto move: moves) {
                if(move.getRowTo() == getSquare().first && move.getColTo() == getSquare().second) return true;
            }

        }
    }
    return false;
}
