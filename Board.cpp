#include <set>

#include "Board.hpp"

Board::Board(const std::vector<std::shared_ptr<Piece>>& pieces_) : pieces{pieces_} {
    std::cout << "Init Board\n";
}

// add piece to pieces vector
void Board::addPiece(const Piece& pc) {
    pieces.push_back(pc.clone());
}

// get squares occupied by friendly pieces
// needed for move generation
std::set<std::pair<int, int>> Board::getOccupiedSquares(bool color) const {
    std::set<std::pair<int, int>> sq;
    for (auto pc: pieces) {
        if(pc->getColor() == color) {
            sq.insert(pc->getSquare());
        }
    }

    return sq;
}

std::ostream& operator<<(std::ostream& os, const Board& bd) {
    os << "Board with: \n";

    os << "White pieces: \n";
    for (auto pc: bd.pieces) if(pc->getColor()) os << *pc;

    os << "Black pieces: \n";
    for(auto pc: bd.pieces) if(!pc->getColor()) os << *pc;

    return os;
}