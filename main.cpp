#include <iostream>
#include <vector>
#include <set>
#include <memory>

#include "Piece.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include "AI.hpp"
#include "Errors.hpp"

#include "Knight.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"

int main() {
    try {
        std::shared_ptr<Board> bd(new Board(BoardFactory::initialBoard()));
        std::cout << *bd;
        // std::shared_ptr<Piece> pc(new Knight(1, 0, true));
        // std::shared_ptr<Move> mv(new Move(1, 0, 0, 2, true, false, false, false, false, ""));

        // bd->addPiece(pc);
        // std::cout << *bd;    

        // std::vector<Move> knightMoves = pc->generatePseudoLegalMoves(*bd);
        // for (const Move& mov: knightMoves) std::cout << mov;

        // std::cout << *pc;

        // // the knight moves from B1 to A3
        // bd->makeMove(*pc, *mv);

        // std::cout << *pc;

        // bd->unmakeMove(*pc, *mv);

        // std::shared_ptr<Piece> k(new King(2, 1, true));

        // pc->generateLegalMoves(dynamic_cast<King&>(*k), knightMoves, *bd);

        // std::cout << AI::evaluateBoard(*bd) << '\n';
        // AI::search(10, *bd);

    } catch (app_error &err) {
        std::cout << "APP ERROR " << err.what() << '\n';
    } catch(std::exception &err) {
        std::cout << err.what() << '\n';
    }

    return 0;
}
