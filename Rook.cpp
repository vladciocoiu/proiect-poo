#include <vector>
#include "Rook.hpp"
#include "Board.hpp"
#include "King.hpp"

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}

std::vector<Move> Rook::generatePseudoLegalMoves(const Board& bd) {   
    auto [currRow, currCol] = getSquare();

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(getColor());

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!getColor());
    
    // signs for all 4 directions
    std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // loop through all directions
    for(std::pair<int, int> sign: dirs) {
        for (int offset = 1; offset < 8; offset++) {
            int newRow = currRow + sign.first * offset;
            int newCol = currCol + sign.second * offset;

            // out of bounds;
            if(newRow >= 8 || newCol >= 8 || newRow < 0 || newCol < 0) break;

            // square is occupied
            if(occupiedSquares.contains({ newRow, newCol })) break;

            // add move
            moves.push_back(Move{currCol, currRow, newCol, newRow, getColor(), enemySquares.contains({ newRow, newCol }), false, false, false, ""});

            // break after finding an enemy piece
            if(enemySquares.contains({ newRow, newCol })) break;
        }
    }

    return moves;
}

int Rook::evaluate(const Board& /*bd*/) {
    return 500;
}
