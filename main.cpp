#include <iostream>
#include <vector>
#include <set>

#include "Piece.hpp"
#include "Board.hpp"
#include "Move.hpp"

int main() {
    Board bd {{}};
    std::cout << bd;
    Piece pc {"knight", 1, 0, true}; // white knight on B1
    bd.addPiece(pc);

    Move mv {1, 0, 0, 2, true, false, false, false, false, ""}; // the knight moves from B1 to A3

    // std::vector<Move> knightMoves = pc.generatePseudoLegalMoves(bd);
    // for (Move mv: knightMoves) std::cout << mv;

    std::cout << pc;

    // pc.makeMove(knightMoves[0]);

    std::cout << pc;

    return 0;
}
