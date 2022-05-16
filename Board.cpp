#include <set>
#include <algorithm>

#include "Board.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"


Board::Board(const std::unordered_set<std::shared_ptr<Piece>>& pieces_) : pieces{pieces_} {
    std::cout << "Init Board\n";
    enPassantCol = -1;
    castleRights = 15;
    turn = true;
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

void Board::makeMove(Piece& piece, const Move& m) {
    pushCastleRights(getCastleRights());
    pushEnPassantCol(getEnPassantCol());
    piece.setSquare({m.getRowTo(), m.getColTo()});

    // TODO: change en passant square when pawn moves up 2 squares
    setEnPassantCol(-1);

    // if castle remove castle rights
    if(m.isCastle()) {
        int castleMask = (piece.getColor() ? 12 : 3);
        setCastleRights(getCastleRights() & castleMask);
    }

    // if king moved (or other piece that is on the initial king square, it doesn't make any difference) remove castle rights
    if(m.getColFrom() == 4 && (m.getRowFrom() == 0 || m.getRowFrom() == 7)) {
        int castleMask = (m.getRowFrom() == 0 ? 12 : 3);
        setCastleRights(getCastleRights() & castleMask);
    }

    // if rook or other piece on its initial square moved, remove castle rights
    if((m.getColFrom() == 0 || m.getColFrom() == 7) && (m.getRowFrom() == 0 || m.getRowFrom() == 7)) {
        int castleMask = (m.getRowFrom() == 0 ? (m.getColFrom() == 0 ? 14 : 13) : (m.getColFrom() == 0 ? 11 : 7));
        setCastleRights(getCastleRights() & castleMask);
    }

    // if capture remove the captured piece and push it to the stack
    if(m.isCapture()) {
        int capturedPieceRow = m.getRowTo() + (m.isEnPassant() ? (turn ? -1 : 1) : 0);
        auto pc = std::find_if(pieces.begin(), pieces.end(), [m, capturedPieceRow](std::shared_ptr<Piece> pc) { 
            return pc->getSquare().first == capturedPieceRow && pc->getSquare().second == m.getColTo();
        });
        if(pc != pieces.end()) {
            pushCapturedPiece(*pc);
            removePiece(*pc);
        }
    }

    // if castle move the rook
    if(m.isCastle()) {
        for(auto pc: pieces) {
            if(pc->getSquare().first == m.getRowTo() && pc->getSquare().second == (m.getColTo() == 6 ? 7 : 0)) {  
                pc->setSquare({m.getRowTo(), (m.getColTo() == 6 ? 5 : 3)});
            }
        }
    }

    if(m.isPromotion()) {
        if(m.getPromotionPiece() == "knight") {
            auto newPiece = std::shared_ptr<Piece>(new Knight{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
            addPiece(newPiece);
        } else if(m.getPromotionPiece() == "bishop")  {
            auto newPiece = std::shared_ptr<Piece>(new Bishop{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
            addPiece(newPiece);
        } else if(m.getPromotionPiece() == "rook") {
            auto newPiece = std::shared_ptr<Piece>(new Rook{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
            addPiece(newPiece);
        } else if(m.getPromotionPiece() == "queen") {
            auto newPiece = std::shared_ptr<Piece>(new Queen{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
            addPiece(newPiece);
        }
        removePiece(piece.clone());
    }
}

void Board::unmakeMove(Piece& piece, const Move& m) {
    if(m.isPromotion())  {
        auto newPiece = std::shared_ptr<Piece>(new Pawn{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
        addPiece(newPiece);
    }
    removePiece(piece.clone());

    if(m.isCastle()) {
        for(auto pc: pieces) {
            if(pc->getSquare().first == m.getRowTo() && pc->getSquare().second == (m.getColTo() == 6 ? 5 : 3)) {  
                pc->setSquare({m.getRowTo(), (m.getColTo() == 6 ? 7 : 0)});
            }
        }
    }

    if(m.isCapture()) addPiece(popCapturedPiece());

    piece.setSquare({m.getRowFrom(), m.getColFrom()});
    setEnPassantCol(popEnPassantCol());
    setCastleRights(popCastleRights());
}