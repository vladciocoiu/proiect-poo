#include "Piece.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Errors.hpp"

#include <unordered_map>

// constructor de initializare
Piece::Piece(int col_, int row_, bool color_) 
: col{col_}, row{row_}, color{color_} {
    if(col_ < 0 || col_ >= 8 || row_ < 0 || row_ >= 8) throw piece_error{"Piece coordinates out of bounds."};
}

// operator <<
std::ostream& operator<<(std::ostream& os, const Piece& pc) {
    os << (pc.color ? "White " : "Black ") << "piece on square ("
       << pc.getSquare().first << ", " << pc.getSquare().second << ")" << '\n';
    return os;
}

// make the move and check if the friendly king is in check
// TODO: fix some bugs here
std::vector<Move> Piece::generateLegalMoves(const King& friendlyKing, const std::vector<Move> &pseudoLegalMoves, Board& bd) {
    std::vector<Move> moves;

    for(const auto &move: pseudoLegalMoves) {
        bd.makeMove(*this, move);

        if(!friendlyKing.isInCheck(bd) && !move.isCastle()) moves.push_back(move);

        bd.unmakeMove(*this, move);
    }

    // special case for castle moves: no square should be attacked between initial and end square of the king
    for(const auto &move: pseudoLegalMoves) {
        if(!move.isCastle()) continue;
        bool ok = true;
        for(auto piece: bd.getPieces()) {
            if(piece->getColor() == color) continue;
            auto mvs = piece->generatePseudoLegalMoves(bd);
            for(auto mv: mvs) {
                if(mv.getRowTo() == row && mv.getColTo() >= std::min(move.getColTo(), move.getColFrom()) && mv.getColTo() <= std::max(move.getColTo(), move.getColFrom())) {
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
        }
        if(ok) moves.push_back(move);
    }

    return moves;
}
