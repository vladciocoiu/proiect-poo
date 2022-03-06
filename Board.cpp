#include <set>

#include "Board.hpp"

Board::Board(std::vector<Piece> pieces_ = {}) : pieces(pieces_) {
        std::cout << "Init Board\n";
    }

// add piece to pieces vector
void Board::addPiece(Piece pc) {
    pieces.push_back(pc);
}

// get squares occupied by friendly pieces
// needed for move generation
std::set<std::pair<char, char>> Board::getOccupiedSquares(bool color) {
    std::set<std::pair<char, char>> sq;
    for (Piece pc: pieces) {
        if(pc.getColor() == color) {
            sq.insert(pc.getSquare());
        }
    }

    return sq;
}

std::ostream& operator<<(std::ostream& os, const Board& bd) {
    os << "Board with: \n";

    os << "White pieces: \n";
    for (Piece pc: bd.pieces) if(pc.getColor()) os << pc;

    os << "Black pieces: \n";
    for(Piece pc: bd.pieces) if(!pc.getColor()) os << pc;

    return os;
}