#include <iostream>
#include <vector>
#include <set>

#include "Piece.hpp"
#include "Board.hpp"
#include "Move.hpp"

#include "Knight.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"

int main() {
    Board bd;
    Knight pc {Piece {1, 0, true}}; // white knight on B1
    bd.addPiece(pc);
    std::cout << bd;    

    Move mv {1, 0, 0, 2, true, false, false, false, false, ""}; // the knight moves from B1 to A3

    std::vector<Move> knightMoves = pc.generatePseudoLegalMoves(bd);
    for (const Move& mov: knightMoves) std::cout << mov;

    std::cout << pc;

    pc.makeMove(mv);

    std::cout << pc;

    return 0;
}
