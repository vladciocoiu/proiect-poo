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
    os << "Board with: ";
    os << "turn=" << (bd.getTurn() ? "white" : "black") << ", ep=" << bd.getEnPassantCol() << ", castle=" << bd.getCastleRights() << '\n';

    os << "White pieces: \n";
    for (auto pc: bd.pieces) if(pc->getColor()) os << *pc;

    os << "Black pieces: \n";
    for(auto pc: bd.pieces) if(!pc->getColor()) os << *pc;

    return os;
}

void Board::makeMove(Piece& piece, const Move& m) {
    switchTurn();
    pushCastleRights(getCastleRights());
    pushEnPassantCol(getEnPassantCol());
    piece.setSquare({m.getRowTo(), m.getColTo()});

    setEnPassantCol(-1);
    if(piece.getPieceType() == "Pawn" && abs(m.getRowTo() - m.getRowFrom()) == 2) setEnPassantCol(m.getColTo());

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

    // if rook or other piece on a1/a8/h1/h8 moved, remove castle rights
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
    switchTurn();
    if(m.isPromotion()) {
        auto newPiece = std::shared_ptr<Piece>(new Pawn{piece.getSquare().second, piece.getSquare().first, piece.getColor()});
        newPiece->setSquare({m.getRowFrom(), m.getColFrom()});
        addPiece(newPiece);
        removePiece(piece.clone());
    } else {
        piece.setSquare({m.getRowFrom(), m.getColFrom()});
    }

    if(m.isCastle()) {
        for(auto pc: pieces) {
            if(pc->getSquare().first == m.getRowTo() && pc->getSquare().second == (m.getColTo() == 6 ? 5 : 3)) {  
                pc->setSquare({m.getRowTo(), (m.getColTo() == 6 ? 7 : 0)});
            }
        }
    }

    if(m.isCapture()) addPiece(popCapturedPiece());

    setEnPassantCol(popEnPassantCol());
    setCastleRights(popCastleRights());
}

int Board::computePieceCount() const {
    int cnt = 0;
    for(auto pc: pieces) {
        cnt += pc->getPieceCount();
    }
    return cnt;
}

std::vector<Move> Board::generateAllLegalMoves() {
    std::vector<Move> moves;

    for(auto pc: pieces) {
        if(pc->getColor() == turn) {
            std::vector<Move> pieceMoves = pc->generateLegalMoves(*this);
            std::copy(pieceMoves.begin(), pieceMoves.end(), std::back_inserter(moves));
        }
    }
    return moves;
}

// finds the piece that should make a certain move
std::shared_ptr<Piece> Board::findPiece(const Move& mv) {
    for(auto pc: pieces) {
        std::vector<Move> pieceMoves = pc->generateLegalMoves(*this);
        if(std::any_of(pieceMoves.begin(), pieceMoves.end(), [mv](auto m) {
                return (m.getColFrom() == mv.getColFrom() && mv.getRowFrom() == m.getRowFrom() && mv.getColTo() == m.getColTo() && mv.getRowTo() == m.getRowTo() && mv.getPromotionPiece() ==  m.getPromotionPiece());
            })) {
            return pc;
        }

    }
    return nullptr;
}

// makes a move that is recieved in Long Algebraic Notation (https://en.wikipedia.org/wiki/Algebraic_notation_(chess)#Long_algebraic_notation)
bool Board::makeMoveFromString(std::string str) {
    int startCol = str[0] - 'a';
    int startRow = str[1] - '1';
    int endCol = str[2] - 'a';
    int endRow = str[3] - '1';
    std::string promotionPiece = "";
    if(str.length() == 5) {
        if(str[4] == 'q') promotionPiece = "queen";
        else if(str[4] == 'r') promotionPiece = "rook";
        else if(str[4] == 'b') promotionPiece = "bishop";
        else promotionPiece = "knight";
    }

    for(auto pc: pieces) {
        if(pc->getColor() == turn) {
            std::vector<Move> pieceMoves = pc->generateLegalMoves(*this);
            auto m = std::find_if(pieceMoves.begin(), pieceMoves.end(), [startCol, startRow, endCol, endRow, promotionPiece](auto mv) { 
                return (mv.getColFrom() == startCol && mv.getRowFrom() == startRow && mv.getColTo() == endCol && mv.getRowTo() == endRow && mv.getPromotionPiece() == promotionPiece);
            });
            if(m != pieceMoves.end()) {
                makeMove(*pc, *m);
                return true;
            }
        }
    }

    return false;
}

Board BoardFactory::initialBoard() {
    BoardBuilder bb;

    // pawns
    for(int row : {1, 6}) {
        for(int col = 0; col < 8; col++) {
            bb.piece(Pawn{col, row, (row == 1)});
        }
    }

    // other pieces
    for(int row : {0, 7}) {
        bb.piece(Knight{1, row, (row == 0)});
        bb.piece(Knight{6, row, (row == 0)});
        bb.piece(Bishop{2, row, (row == 0)});
        bb.piece(Bishop{5, row, (row == 0)});
        bb.piece(Rook{0, row, (row == 0)});
        bb.piece(Rook{7, row, (row == 0)});
        bb.piece(Queen{3, row, (row == 0)});
    }    

    // kings
    King wk{4, 0, true}, bk{4, 7, false};
    bb.piece(wk).piece(bk).whiteKing(wk).blackKing(bk);

    return bb.turn(true).castleRights(15).epCol(-1).build();
}
