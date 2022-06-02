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
#include "MyStack.hpp"

int main() {
    try {
        std::shared_ptr<Board> bd(new Board(BoardFactory::initialBoard()));
        MyStack<Move> stk;


        // game loop
        while(true) {
            // user move (in Long Algebraic Notation)
            std::string s;
            std::cin >> s;

            if(s == "quit") return 0;

            bool success = bd->makeMoveFromString(s);

            if(!success) continue;

            // AI move
            auto res = AI::search(2, *bd);
            stk.push(res.second);

            std::cout << "Evaluation: " << res.first << " centipawns\nMove: " << res.second << '\n';

            auto piece = bd->findPiece(res.second);
            if(piece == nullptr) break;

            bd->makeMove(*piece, res.second);
        }
        stk.print();

    } catch (app_error &err) {
        std::cout << "APP ERROR " << err.what() << '\n';
    } catch(std::exception &err) {
        std::cout << err.what() << '\n';
    }

    return 0;
}
